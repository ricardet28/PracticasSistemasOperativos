#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sched.h>
#include <pthread.h>
#define num_cpu 4

int trozo[num_cpu + 1];
int vectorSumasParciales[num_cpu];

void * func (void * argumento){

  int i = *((int *)argumento);
  //printf("El argumento recibido es: %d\n", i);
  int sumaParcial = 0;
  for (int j = trozo[i]; j<trozo[i+1]; j++){

    sumaParcial = sumaParcial + (j+1);

  }
  vectorSumasParciales[i] = sumaParcial;
  printf("El thread %lu del proceso %d realiza la suma parcial desde %d hasta %d = %d\n", pthread_self(), getpid(), trozo[i] + 1, trozo[i+1], sumaParcial);

}

int GetCPUCount()
{
  int count = 0;
  cpu_set_t cs;
  sched_getaffinity(0,sizeof(cs),&cs);

  for (size_t i = 0; i < sizeof(cs); i++) {
    if(CPU_ISSET(i,&cs)) count++;
  }

  return count;
}

int main (int argc, char * argv[])
{

  int i;
  int v = GetCPUCount(); //numero de cachos en los que hacer la suma
  int sumasParciales[2];
  int N = atoi(argv[1]); //num a sumar todos sus num anteriores

  trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */
  for (i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */
  for (i=0; i<(v+1); i++)
    printf("Trozo %d: %d\n",i,trozo[i]);

  vectorSumasParciales[v];

  int vectorIteradores[v];
  for (int i = 0; i<v; i++){
    vectorIteradores[i] = i;
  }

  pthread_t hilos[v];
  for (int i=0;i<v; i++){
    pthread_create(&hilos[i], NULL, func, (void *)&vectorIteradores[i]);
  }

  for (int i=0; i<v; i++){
    pthread_join(hilos[i], NULL);
  }

  for (int i=0; i<v; i++){
    printf("vectorSumasParciales[%d] = %d\n", i, vectorSumasParciales[i]);
  }
  int sumaTotal = 0;
  for (int i=0;i<v; i++){
    sumaTotal = sumaTotal + vectorSumasParciales[i];
  }
  printf("La suma total es: %d\n",sumaTotal);
  exit(0);


}
