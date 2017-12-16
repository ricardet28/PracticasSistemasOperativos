#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>

#define N 5
#define M 5

long int array[N][M];

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

int main(int argc, char * argv[])
{

  int c1, c2;

  struct timeval t_ini, t_fin;
  double secs;
  srand ( time(NULL) );

  int v = atoi(argv[1]);





  gettimeofday(&t_ini, NULL); /* obtiene tiempo inicial */

  int tubos[v][2];
  for (int i=0; i<v; i++){

    pipe(tubos[i]);

  }

  int trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */

  for (int i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */

  for (int i=0; i<(v+1); i++)
    printf("Trozo %d: %d\n\n",i,trozo[i]);



  //montamos una matriz con randoms
  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;

  printeaMatriz();

  for (int i=0; i<v; i++){
    if (fork()==0){
      close(tubos[i][0]);
      for (int j=trozo[i]; j<trozo[i+1]; j++){ //recorre x filas a ordenar
        ordena(j);//ordena una de esas filas
        printf("Fila %d ordenada por el proceso %d\n", j, getpid());
      }
      for (int j = trozo[i]; j<trozo[i+1]; j++){
        for (int k = 0; k < M; k++) {
          int dato = array[j][k];
          write(tubos[i][1], &dato, sizeof(dato));
        }

      }
      close(tubos[i][1]);
      exit(0);
    }
  }

  for (int i=0; i<v; i++){
    wait(0);
  }
  gettimeofday(&t_fin, NULL); /* obtiene tiempo final */

  secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
  printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);

  printf("____________________________MATRIZ ORDENADA_______________________________\n");

  for (int i=0; i<v; i++){

      for (int j = trozo[i]; j<trozo[i+1];  j++){

          for (int k=0; k<M; k++){
              int dato;
              if (read(tubos[i][0], &dato, sizeof(dato))>0){
                array[j][k] = dato;
              }

          }

      }

  }







  printeaMatriz();
  exit(0);
}
