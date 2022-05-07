// ls1.c
// affiche une description du fichier / répertoire indiqué
//
// usage: ls1 fichier


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>

void montrer_elements( const char * chemin)
{
  DIR *dir = opendir(chemin);
  struct dirent *entree;
  while ((entree = readdir(dir)) != NULL) {
    printf("\t%s\n", entree -> d_name);
  }
  closedir(dir);
}

void montrer(const char * chemin) 
{
    struct stat s;
    if (stat(chemin, &s) != 0) {
      perror("stat");
      return;
    }

    if ( S_ISREG(s.st_mode)) {
      printf("f %8zu %s\n", s.st_size, chemin);
    } else if ( S_ISDIR(s.st_mode)) {
      printf( "d        %s\n", chemin);
      montrer_elements(chemin);      
    } else {
      printf( "?        %s\n", chemin);
    }    
}


int main(int argc, char **argv)
{
  if (argc == 1) {
    montrer(".");
  } else {
    for (int i=1; i < argc; i++) {
      montrer(argv[i]);
    }
  }
  return EXIT_SUCCESS;
}

