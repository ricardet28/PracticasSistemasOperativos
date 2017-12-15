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


#define N 8
#define M 8

long int array[N][M];

/* devuelve "a - b" en segundos */
double timeval_diff(struct timeval *a, struct timeval *b) {
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
}


void imprimirMatriz(){

	for (int i = 0; i<N; i++){
		printf("\n");
		for (int j=0;j<M;j++){
			printf("%ld ", array[i][j]);

		}
	}
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

void imprimir(int fila_aux)
{
  //printf("fila numero %d", fila_aux);
  for (int i=0; i<M;i++)
  {
    printf("%ld ", array[fila_aux][i]);
  }
  printf("\n");
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

int main(int argc, char * argv[]){
  srand(time(NULL));
  int c1, c2;
  struct timeval t_ini, t_fin;
  double secs;
  int i=0;

  pid_t pid;

  int v = GetCPUCount();
  int pipeArray[v][2];

  for (size_t i = 0; i < v; i++) //inicializamos las pipes, tantas como procesos
  {
    pipe(pipeArray[i]);
  }

  int trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */

  for (i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */

  for (i=0; i<(v+1); i++) {
    printf("Trozo %d: %d\n",i,trozo[i]);
  }

  //CREAMOS LA MATRIZ
  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;


  imprimirMatriz();
  printf("\n");

  long int dato;
  int procNum;
  int from;
  int to;
  int j = 0;

  for (procNum = 0; procNum < v; procNum++)
  {
    gettimeofday(&t_ini, NULL);
    from = trozo[procNum];
    to = trozo[procNum + 1];
    pid = fork();

    if (pid==0) // solo los hijos
    {
        close(pipeArray[procNum][0]);

        for (j=from; j<to;j++)
        {
          ordena(j);
        }

         //escribimos enlatuberia lo q ha ordenado
        for (size_t i = from; i < to; i++)
         {
           for (size_t k = 0; k < M; k++)
            {
              dato = array[i][k];
              write(pipeArray[procNum][1], &dato, sizeof(dato));
            }
        }

        close(pipeArray[procNum][1]);
	gettimeofday(&t_fin, NULL);
	secs = timeval_diff(&t_fin, &t_ini);
	printf("Tiempo consumido por el proceso %d: %.16g milisegundos \n\n", (int)j, secs * 1000.0);



        exit(0);
    }



    for (int i=0; i<v;i++)
      wait(0);
  }

  dato = 0;
  for (size_t i = 0; i < v; i++)//recorre todos los procesos que hemos creado
  {
    for (size_t j = trozo[i]; j <trozo[i+1]  ; j++)
    {
        for (size_t k = 0; k < M; k++)
        {
          if (read(pipeArray[i][0], &dato, sizeof(dato)) > 0)
          {
            array[j][k] = dato;
            //printf("%ld, ",dato);
          }
        }
      
    }
  }
  printf("\n");

  imprimirMatriz();

  exit(0);
}
