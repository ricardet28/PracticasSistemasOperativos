
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char * argv[])
{
  int n = atoi(argv[1]);
  int counter = 0;
  int t1[2];
  int t2[2];
  int t3[2];
  pipe(t1);
  pipe(t2);
  pipe(t3);
  int proximo = 1;
  write(t1[1], &proximo, sizeof(proximo));

  printf("%d\n", counter);
  if (fork()==0){ //proceso 1
    proximo = 2;
    close(t2[0]);
    close(t3[0]);
    close(t3[1]);
    int dato;
    //testigo = read(t1[0], &dato, sizeof(int));
    while (read(t1[0], &dato, sizeof(dato))>0){
      if (dato == 1){
        counter++;
        printf("%d\n", counter);

        printf("proceso 1 con PID: %d\n", getpid());
        write(t2[1], &proximo, sizeof(proximo)); //escribe en proceso 2
        //write(t1[1], 0, sizeof(int));

      }
      if (counter==n){
        exit(0);
      }
    }
  }

  if (fork() == 0){ //proceso 2
    proximo = 3;
    close(t1[1]);
    close(t3[0]);
    close(t1[0]);
    int dato;
    while (read(t2[0], &dato, sizeof(dato))>0){

      if (dato == 2){
        counter++;
        printf("%d\n", counter);

        printf("proceso 2 con PID: %d\n", getpid());
        write(t3[1], &proximo, sizeof(proximo)); //escribe en proceso 3
        //write(t2[1], 0, sizeof(int));
      }
      if (counter==n){
        exit(0);
      }
    }
  }

  if (fork() == 0){//proceso 3
    proximo = 1;
    close(t1[0]);
    close(t2[0]);
    close(t2[1]);
    int dato;
    while (read(t3[0], &dato, sizeof(dato))>0){
      if (dato == 3){
        counter++;
        printf("%d\n", counter);

        printf("proceso 3 con PID: %d\n", getpid());
        write(t1[1], &proximo, sizeof(proximo)); //escribe en proceso 1
        //write(t3[1], 0, sizeof(int));

      }
      if (counter==n){
        exit(0);
      }

    }
  }

  wait(0);
  wait(0);
  wait(0);
  printf("sale padre");
  exit(0);
}
