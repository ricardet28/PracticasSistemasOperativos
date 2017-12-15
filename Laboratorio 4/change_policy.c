#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sched.h>
#include <sys/resource.h>

#define N 1000
#define M 1000

long int array[N][M];

/* devuelve "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b) {
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}

void ordena(int numero_aux)
{
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

int main()
{
  int c1, c2;
  struct timeval t_ini, t_fin;
  double secs;


  srand ( time(NULL) );

  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;

  gettimeofday(&t_ini, NULL); /* obtiene tiempo inicial */
  
  if (fork()==0){//crea proceso hijo 1

	
	int valor;

	int policy, ret, x;
	struct sched_param sp;
	

	//valor = getpriority(PRIO_PROCESS, 0);
	//printf("Prioridad del proceso %d: %d\n", getpid(), valor);

	
	

	

		
	sched_getparam(0, &sp);
	printf("Politica CFS. Prioridad fija: %d\n", sp.sched_priority);
	sp.sched_priority = 1;
	sched_setscheduler(0, SCHED_RR, &sp);
	sp.sched_priority =1;
	sched_setparam(0, &sp);

	policy = sched_getscheduler(0);
	
	
	if (policy == SCHED_RR)
		printf("Politica RR. Prioridad fija: %d\n", sp.sched_priority);

	/*
	setpriority(PRIO_PROCESS, 0, -10);
	valor = getpriority(PRIO_PROCESS, 0);
	printf("Nueva prioridad del proceso hijo 1 %d: %d\n", getpid(), valor);	
	*/
	for ( c1 = 0 ; c1 < N/2 ; c1++){

    			ordena(c1);
	}
	printf("Listas ordenadas en orden ascendente por el primer hijo:\n");
/*
	for ( c1 = 0 ; c1 < N ; c1++)
	{
	    printf("Columna %d: ", c1);
	    for ( c2 = 0 ; c2 < M ; c2++ )
	        printf("%ld ", array[c1][c2]);
	    printf("\n");
	}
*/
	gettimeofday(&t_fin, NULL); /* obtiene tiempo final */

  	secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  	printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);
	exit(0);
	
	
  }
  
  if (fork()==0){//crea proceso hijo 2
	
	setpriority(PRIO_PROCESS, 0, -20);
	int valor;
	//valor = getpriority(PRIO_PROCESS, 0);
	//printf("Prioridad del proceso %d: %d\n", getpid(), valor);
	
	
	valor = getpriority(PRIO_PROCESS, 0);

	printf("Nueva prioridad del proceso hijo 2 %d: %d\n", getpid(), valor);        

	for ( c2 = N/2 ; c2 < N ; c2++){
    		ordena(c2);	
	}
	printf("Listas ordenadas en orden ascendente por el segundo hijo:\n");
/*
	  for ( c1 = 0 ; c1 < N ; c1++)
	    {
	      printf("Columna %d: ", c1);
	      for ( c2 = 0 ; c2 < M ; c2++ )
		printf("%ld ", array[c1][c2]);
	      printf("\n");
	    }
*/
	gettimeofday(&t_fin, NULL); /* obtiene tiempo final */

  	secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  	printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);
	exit(0);
	
  }
 



  for (int i=0; i<2; i++){
	wait(0);
  }
  gettimeofday(&t_fin, NULL); /* obtiene tiempo final */

  secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  

  

  exit(0);
}
