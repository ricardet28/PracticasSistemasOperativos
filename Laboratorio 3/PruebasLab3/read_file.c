#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>

int main(){

  char dato, fd;
  
  fd = open("VelesEVents", O_RDONLY);
  while (read(fd, &dato, sizeof(char))>0){

    printf("%c", dato);



  }
  close(fd);
  exit(0);




}
