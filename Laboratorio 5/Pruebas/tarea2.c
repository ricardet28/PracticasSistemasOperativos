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



void * func(void * argumento){

  int valor = *((int * )argumento);
  int factorial = 1;
  for (int i=valor; i>0; i--){
    factorial = factorial * i;
  }
  printf("El thread %lu del proceso %d calcula el factorial de %d = %d\n", pthread_self(), getpid(), valor, factorial);
  pthread_exit(0);
}


int main(int argc, char * argv[]){

  int n = argc - 1;
  pthread_t hilos[n];
  int vec[n];
  for (int i= 0; i<n; i++){
    vec[i] = atoi(argv[i + 1]);
  }
  for (int i = 0; i<n; i++){

    pthread_create(&hilos[i], NULL, func, (void *)&vec[i]);

  }
  for (int i = 0; i<n; i++){

    pthread_join(hilos[i], NULL);
  }

  printf("El padre sale! \n");





}
