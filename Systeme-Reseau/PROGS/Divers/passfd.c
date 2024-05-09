/*
 Exemple adapté de
 http://www.mail-archive.com/
 linux-development-sys@senator-bedfellow.mit.edu/msg01240.html
 (remplacement de alloca par malloc + modifications mineures)
 */

/*
 * This program shows how to transmit an (open) file descriptor
 * to another process avor a local socket.
 *
 * It behaves like a simple /bin/cat, with 1 filename as argument.
 * 
 * It forks a child process, which opens a file, and then sends 
 * its name and file descriptor to the parent process, in a message
 * though a socket.
 * The parent process receives it, and displays the data using the 
 * file descriptor.
 * 
 * It works due to the SCM_RIGHTS type for the control message,
 * which allows to transmit file descriptors or process credentials
 * over local sockets. See the unix (7) man page.
 */

#include <malloc.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <sys/un.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void die (char *message)
{
    perror(message);
    exit(EXIT_FAILURE);
}

/* 
 * Copies data from file descriptor 'from' to file descriptor 'to'
 * Exits if an error occurs.   
 */
void copyData (int from, int to)
{
    char buf[1024];
    int amount;
    while ((amount = read(from, buf, sizeof(buf))) > 0) {
        if (write(to, buf, amount) != amount) {
            die("write");
        }
    }
    if (amount < 0) {
        die("read");
    }
}

/*
  The child process.
  Opens the file and send its descriptor.
*/
int childProcess (char *filename, int sock)
{
    int fd = open(filename, O_RDONLY);

    // Open the file whose descriptor will be passed.
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }

    // buffer for filename to be sent
    struct iovec vector = {
        .iov_base = filename,             // address
        .iov_len = strlen(filename) + 1   // size
    };

    // a message is a struct with
    // - a header with some members (see man msg), including
    // an array of iovec to transmit buffers.
    // - a flexible array member for data 
    // (see https://en.wikipedia.org/wiki/Flexible_array_member)

    // the first part of the message, with filename in vector
    struct msghdr message = {	
        .msg_iov = &vector,
        .msg_iovlen = 1
    };

    // Allocate the control message header with room for file descriptor.
    size_t len = sizeof(message) + sizeof(fd);
    struct cmsghdr *control = malloc(len);

    control->cmsg_len = len;
    control->cmsg_level = SOL_SOCKET;
    control->cmsg_type = SCM_RIGHTS;

    // for SCM_RIGHT type, the data is an array of file descriptors
    memcpy(CMSG_DATA(control), &fd, sizeof(fd));

    message.msg_control = control;
    message.msg_controllen = control->cmsg_len;

    if (sendmsg(sock, &message, 0) != (ssize_t) vector.iov_len) {
        die("sendmsg");
    }

    free(control);
    return EXIT_SUCCESS;
}

/*
    The parent process.
    Receives the file descriptor and displays the content.
*/

int parentProcess (int sock)
{
    char filename[1000];	

    struct iovec vector = {
        .iov_base = filename,
        .iov_len = sizeof(filename),
    };

    struct msghdr message = {	
        .msg_iov = &vector,
        .msg_iovlen = 1
    };

    int fd;
    char header_buffer[sizeof(struct cmsghdr) + sizeof(fd)];
    struct cmsghdr *header = (struct cmsghdr *) header_buffer;

    header->cmsg_len = CMSG_LEN(sizeof(struct cmsghdr) + sizeof(fd));
    message.msg_control = header;
    message.msg_controllen = header->cmsg_len;

    if (!recvmsg(sock, &message, 0)) {
        return EXIT_FAILURE;
    }

    printf("got file descriptor for '%s'\n", (char *) vector.iov_base);

    // get the file descriptor from the data
    memcpy(&fd, CMSG_DATA(header), sizeof(fd));
    copyData(fd, 1);
  
    return EXIT_SUCCESS;
}

/*
 * main
 */  

int main (int argc, char **argv)
{
    if (argc != 2) {
        fprintf(stderr, "only a single argument is supported\n");
        return 1;
    }

    // Create the sockets. One for the parent and other for the child
    int socks[2];
    if (socketpair(PF_UNIX, SOCK_STREAM, 0, socks)) {
        die("socketpair");
    }

    if (fork() == 0) { // child
        close(socks[0]);
        return childProcess(argv[1], socks[1]);
    }

    close(socks[1]); // parent
    parentProcess(socks[0]);

    int status;
    wait(&status);

    if (WEXITSTATUS(status)) {
        fprintf(stderr, "child failed\n");
    }

    return EXIT_SUCCESS;
}
