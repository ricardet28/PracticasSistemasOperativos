#include <unistd.h>
#include <sched.h>
#include <math.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/math.h>
#include <pthread.h>
#include <sys/syscall.h>
#include <stdlib.h>

#define numberCPUS 1;

int trozo[numberCPUS + 1];
int main(int argc, char * argv[]){
  createMatrix();
  imprimeMatriz();
  int v = GetCPUCount();
  //int trozo[v+1];
  double aux = (double) N/v;

  for (int i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i);

  for (int i=0; i<v; i++)
    printf("Trozo %d: %d\n", i, trozo[i]);

  int vectorIteraciones[v];
  for (int i=0; i<v; i++)
    vectorIteraciones[i] = i;

  pthread_t hilo[v];
  for (int i=0; i<v; i++)
    pthread_create(&hilo[i], NULL, func, (void*)&vectorIteraciones[i]);

  for (int i=0;i<v; i++)
    pthread_join(hijo[i], NULL);
  printf("\n\nMATRIZ ORDENADA____________________________________\n");
  imprimirMatriz();
  exit(0);

}
void createMatrix(){
  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;
}
void *func(void *numero){

  int from = *((int *)numero);
  for (int i=trozo[from]; i<trozo[from + 1]; i++)
    ordena(i);

  pthread_exit(0);
}

int GetCPUCount(){
  int i, count=0;
  cpu_set_t cs;
  for (i = 0; i<sizeof(cs); i++){
    if (CPU_ISSET(i, &cs))count++;
  }
  return count;
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

