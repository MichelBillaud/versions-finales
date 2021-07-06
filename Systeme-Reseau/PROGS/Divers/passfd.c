
/*
 exemple adapté de
 http://www.mail-archive.com/
 linux-development-sys@senator-bedfellow.mit.edu/msg01240.html
 (remplacement de alloca par malloc + modifications mineures)
 */

/* passfd.c -- sample program which passes a file descriptor */

/* We behave like a simple /bin/cat, which only handles one argument
 *    (a file name). We create Unix domain sockets through
 *    socketpair(), and then fork(). The child opens the file whose
 *    name is passed on the command line, passes the file descriptor
 *    and file name back to the parent, and then exits. The parent
 *    waits for the file descriptor from the child, then copies data
 *    from that file descriptor to stdout until no data is left. The
 *    parent then exits. */

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


/* Copies data from file descriptor 'from' to file descriptor 'to'
 *    until nothing is left to be copied.
 Exits if an error occurs.   */
void copyData (int from, int to)
{
    char buf[1024];
    int amount;
    while ( (amount = read(from, buf, sizeof(buf))) > 0) {
        if (write(to, buf, amount) != amount) {
            die("write");
        }
    }
    if (amount < 0)
        die("read");
}

/* The child process. This sends the file descriptor. */
int childProcess (char *filename, int sock)
{
    int fd = open(filename, O_RDONLY);

    /* Open the file whose descriptor will be passed. */
    if (fd < 0) {
        perror("open");
        return EXIT_FAILURE;
    }


    /* Send the file name down the socket, including the trailing '\0' */
    struct iovec vector = {	/* some data to pass w/ the fd */
        .iov_base = filename,
        .iov_len = strlen(filename) + 1
    };

    /* Put together the first part of the message.
       Include the file name iovec */
    struct msghdr msg = {	/* the complete message */
        .msg_name = NULL,
        .msg_namelen = 0,
        .msg_iov = &vector,
        .msg_iovlen = 1
    };
    /* Now for the control message. We have to allocate room for
     *        the file descriptor. */

    struct cmsghdr *cmsg;	/* the control message,
				   which will include the fd */
    size_t len = sizeof(struct cmsghdr) + sizeof(fd);
    cmsg = malloc(len);
    cmsg->cmsg_len = len;
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;

    /* copy the file descriptor onto the end of
    the control message */
    memcpy(CMSG_DATA(cmsg), &fd, sizeof(fd));

    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    if (sendmsg(sock, &msg, 0) != (ssize_t) vector.iov_len) {
        die("sendmsg");
    }

    free(cmsg);
    return EXIT_SUCCESS;
}

/* The parent process. This receives the file descriptor. */
int parentProcess (int sock)
{
    char buf[80];		/* space to read file name into */

    struct cmsghdr *cmsg;	/* control message with the fd */
    int fd;

    /* set up the iovec for the file name */
    struct iovec vector = {	/* file name from the child */
        .iov_base = buf,
        .iov_len = 80,
    };

    /* the message we're expecting to receive */
    struct msghdr msg = {	/* full message */
        .msg_name = NULL,
        .msg_namelen = 0,
        .msg_iov = &vector,
        .msg_iovlen = 1
    };;

    /* dynamically allocate so we can leave room for the file
     *        descriptor */
    cmsg = malloc(sizeof(struct cmsghdr) + sizeof(fd));
    cmsg->cmsg_len = sizeof(struct cmsghdr) + sizeof(fd);
    msg.msg_control = cmsg;
    msg.msg_controllen = cmsg->cmsg_len;

    if (!recvmsg(sock, &msg, 0)) {
        return EXIT_FAILURE;
    }

    printf("got file descriptor for '%s'\n", (char *) vector.iov_base);

    /* grab the file descriptor from the control structure */
    memcpy(&fd, CMSG_DATA(cmsg), sizeof(fd));
    copyData(fd, 1);
    free(cmsg);

    return EXIT_SUCCESS;
}

int main (int argc, char **argv)
{
    int socks[2];
    int status;

    if (argc != 2) {
        fprintf(stderr, "only a single argument is supported\n");
        return 1;
    }

    /* Create the sockets. The first is for the parent and the
     *        second is for the child (though we could reverse that
     *        if we liked. */
    if (socketpair(PF_UNIX, SOCK_STREAM, 0, socks)) {
        die("socketpair");
    }

    if ( fork() == 0 ) { /* child */
        close(socks[0]);
        return childProcess(argv[1], socks[1]);
    }

    /* parent */
    close(socks[1]);
    parentProcess(socks[0]);

    wait(&status);

    if (WEXITSTATUS(status)) {
        fprintf(stderr, "child failed\n");
    }

    return EXIT_SUCCESS;
}
