#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

#define N 7
#define M 8

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

void imprimir(int fila_aux){
  //printf("fila numero %d", fila_aux);
  for (int i=0; i<M;i++){

    printf("%ld ", array[fila_aux][i]);
  }
  printf("\n");



}


int main(int argc, char * argv[])
{
  int n_proc=atoi(argv[1]);
  int c1, c2;
  struct timeval t_ini, t_fin;
  double secs;
  int counter = -1;

  pid_t pid;

  n_proc = N; //en caso de no ser asi, comentar esta linea de codigo.


  for ( c1 = 0 ; c1 < N ; c1++)
    for ( c2 = 0 ; c2 < M ; c2++ )
      array[c1][c2] = rand() % 100;

  c1=0;
  c2=0;

  for (int procNum =0; procNum<n_proc; procNum++){

    c1 = procNum;

    pid = fork();

    if (pid==0){

            printf("Soy: %d y mi papa es: %d", getpid(), getppid());
            printf("\n");
            ordena(c1);
            imprimir(c1);

            break;






    }
    


    else{

      for (int i=0; i<n_proc;i++){
          //espera a todos los procesos hijos a que acaben
          wait(0);

      }

    }






  }
  //fuera del for
  if (pid==0){

          exit(0);

  }




  //srand ( time(NULL) );




/*  gettimeofday(&t_ini, NULL);





  //PRIMER HIJO
  if (fork()==0){
	for ( c1 = 0 ; c1 < N/2 ; c1++){

    		ordena(c1);




	}
	printf("Listas ordenadas en orden ascendente por el primer hijo:\n");
	for ( c1 = 0 ; c1 < N ; c1++)
	{
	    printf("Columna %d: ", c1);
	    for ( c2 = 0 ; c2 < M ; c2++ )
	        printf("%ld ", array[c1][c2]);
	    printf("\n");
	}
	gettimeofday(&t_fin, NULL);

  	secs = timeval_diff(&t_fin, &t_ini);
  	printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);
	wait(0);
	exit(0);

  }
  //SEGUNDO HIJO
  if (fork()==0){

	for ( c2 = N/2 ; c2 < N ; c2++){
    		ordena(c2);



	}
	printf("Listas ordenadas en orden ascendente por el segundo hijo:\n");
	  for ( c1 = 0 ; c1 < N ; c1++)
	    {
	      printf("Columna %d: ", c1);
	      for ( c2 = 0 ; c2 < M ; c2++ )
		printf("%ld ", array[c1][c2]);
	      printf("\n");
	    }
	gettimeofday(&t_fin, NULL);

  	secs = timeval_diff(&t_fin, &t_ini);
  	printf("Tiempo consumido: %.16g milisegundos\n\n", secs * 1000.0);


  }





  gettimeofday(&t_fin, NULL);

  secs = timeval_diff(&t_fin, &t_ini);
  */



  exit(0);
}
