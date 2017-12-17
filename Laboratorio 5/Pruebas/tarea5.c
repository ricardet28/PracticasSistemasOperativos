#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sched.h>
#include <pthread.h>

#define N 100
#define M 100
#define num_cpu 4
long int array[N][M];
int trozo[num_cpu + 1];
/* devuelve "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b) {
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

void ordena(int numero_aux){
  int position, d, c;
  long int swap;

  for ( c = 0 ; c < ( M - 1 ) ; c++ )
    {
      position = c;

      for ( d = c + 1 ; d < M ; d++ )
	{
	  if ( array[numero_aux][position] > array[numero_aux][d] )
            position = d;
	}
      if ( position != c )
	{
	  swap = array[numero_aux][c];
	  array[numero_aux][c] = array[numero_aux][position];
	  array[numero_aux][position] = swap;
	}
    }
}

void printeaMatriz(){
	for ( int c1 = 0 ; c1 < N ; c1++)
	{
	      printf("Columna %d: ", c1);
	      for ( int c2 = 0 ; c2 < M ; c2++ )
			printf("%ld ", array[c1][c2]);
	      printf("\n");
	}


}

void * func(void * argumento){
  int i = *((int *)argumento);
  for (int j=trozo[i]; j<trozo[i+1];j++){
    ordena(j);
    printf("Thread %lu del proceso %d ordena la fila %d\n", pthread_self(), getpid(), j);
  }
  pthread_exit(0);
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

int main(int argc, char * argv[])
{
  struct timeval t_ini, t_fin;
  double secs;
  srand ( time(NULL) );
  gettimeofday(&t_ini, NULL); /* obtiene tiempo inicial */

  int v = GetCPUCount();

  trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */
  for (int i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */
  for (int i=0; i<(v+1); i++)
    printf("Trozo %d: %d\n\n",i,trozo[i]);

  //montamos una matriz con randoms
  int c1, c2;
  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;

  printeaMatriz();

  int vectorIteradores[v];
  for (int i=0; i<v; i++){
    vectorIteradores[i] = i;
  }

  pthread_t hilos[v];
  for (int i=0; i<v; i++){
    pthread_create(&hilos[i], NULL, func, (void *)&vectorIteradores[i]);
  }

  for (int i=0; i<v; i++){
    pthread_join(hilos[i], NULL);
  }

  gettimeofday(&t_fin, NULL); /* obtiene tiempo final */
  secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);

  //printf("____________________________MATRIZ ORDENADA_______________________________\n\n");

  printeaMatriz();
  exit(0);
}
