#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>

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

void printeaMatriz(){



	for ( int c1 = 0 ; c1 < N ; c1++)
	{
	      printf("Columna %d: ", c1);
	      for ( int c2 = 0 ; c2 < M ; c2++ )
			printf("%ld ", array[c1][c2]);
	      printf("\n");
	}

  
}

int main()
{
  int c1, c2;
  struct timeval t_ini, t_fin;
  double secs;


  srand ( time(NULL) );


  //montamos una matriz con randoms
  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;

  gettimeofday(&t_ini, NULL); /* obtiene tiempo inicial */

 
  
  for (int i= 0; i<N; i++){
	
	ordena(i);

  }


  
  gettimeofday(&t_fin, NULL); /* obtiene tiempo final */

  secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);


  //muestra por pantalla
  //printf("Listas ordenadas en orden ascendente:\n");
  
  exit(0);
}
