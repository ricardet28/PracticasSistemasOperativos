#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <sys/wait.h>
#include <pthread.h>

void * func(void * saludo){

  int valor = *((int *)saludo);
  int factorial = 1;
  for (int i = valor; i>0; i--){
    factorial = factorial * i;
  }
  printf("El thread %lu del proceso %d calcula factorial de %d = %d\n", pthread_self(), getpid(), valor, factorial);
  pthread_exit(0);
}
int main(int argc, char * argv[]){

  int a = atoi(argv[1]);
  int b = atoi(argv[2]);

  pthread_t hilos[2];
  pthread_create(&hilos[0], NULL, func, (void *)&a);
  pthread_create(&hilos[1], NULL, func, (void *)&b);

  pthread_join(hilos[0], NULL);
  pthread_join(hilos[1], NULL);

  printf("Proceso padre sale! \n");
  exit(0);

}
