/* aprox_eq N v ---> obtiene los números enteros, entre el 0 y el N, de manera que (en N) haya v regiones de tamaño similar */
/* el resultado se guarda en el vector trozo[] */
/* ejemplo: aprox_eq 8 2 devuelve 0 4 8 */
/* ejemplo: aprox_eq 8 3 devuelve 0 2 5 8 */

#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <pthread.h>
#include <sys/syscall.h>

#define numeroCPUS 3
int sumaTotal;
int trozo[numeroCPUS + 1];
pthread_mutex_t mutex;

double secs;
struct timeval t_ini, t_fin;

double timeval_diff(struct timeval *a, struct timeval *b){

	return
		(double)(a->tv_sec + (double)a->tv_usec/1000000) -
		(double)(b->tv_sec + (double)b->tv_usec/1000000);
}


void *func(void *numero){
  int i;
	int sumaParcial = 0;
	int from = *((int *) numero);


	for (i=trozo[from]; i<trozo[from + 1]; i++){

		sumaParcial = sumaParcial + (i + 1);
	}


	pthread_mutex_lock(&mutex);
	sumaTotal = sumaTotal + sumaParcial;
	pthread_mutex_unlock(&mutex);



	printf("PID %d Thread %lu TaskID %ld realiza suma %d = %d\n\n", getpid(), pthread_self(), syscall(SYS_gettid), from, sumaParcial);

	gettimeofday(&t_fin, NULL);
	secs = timeval_diff(&t_fin, &t_ini);
	printf("Tiempo consumido por el proceso %d: %.16g milisegundos \n\n", getpid(), secs * 1000.0);
	pthread_exit(0);
}

int GetCPUCount(){

  int i, count=0;
  cpu_set_t cs;
  sched_getaffinity(0,sizeof(cs), &cs);

  for (size_t i= 0; i< sizeof(cs); i++){

	if (CPU_ISSET(i, &cs)) count++;

  }

  return count;

}

int main (int argc, char * argv[])
{
  pthread_mutex_init(&mutex, NULL);

	srand(time(NULL));
	gettimeofday(&t_ini, NULL);


  int i;
  int v = GetCPUCount();
	trozo[v+1];
  int N = atoi(argv[1]);

	//int n= sizeof(trozo) / sizeof(n);
	//printf("vector trozo mide: %d\n", n);
  double aux = (double) N/v; /* casting de tipos */

  for (i=0; i<(v+1); i++){

    trozo[i] = (int) (aux * i); /* casting de tipos */
  }

  for (i=0; i<(v+1); i++) {

    printf("Trozo %d: %d\n",i,trozo[i]);
  }



	int vectorIteraciones[v];
	for (int i= 0; i<v; i++){

		vectorIteraciones[i] = i;

	}
  pthread_t hilo[v];
	gettimeofday(&t_ini, NULL);
  for (int j=0; j<v; j++){

		int this = j;
		pthread_create(&hilo[j], NULL, func, (void*) &vectorIteraciones[j]);

  }
  for (int j = 0; j<v+1; j++){
		pthread_join(hilo[j], NULL);
		printf("Hilo %d finalizado. \n", j);
  }







  printf("\n\nLa suma total: %d \n", sumaTotal);
	pthread_mutex_destroy(&mutex);
  exit(0);

}
