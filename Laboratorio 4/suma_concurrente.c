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

double timeval_diff(struct timeval *a, struct timeval *b){

	return
		(double)(a->tv_sec + (double)a->tv_usec/1000000) - 
		(double)(b->tv_sec + (double)b->tv_usec/1000000);
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
  srand(time(NULL));
  struct timeval t_ini, t_fin;
  cpu_set_t cs;
  CPU_ZERO(&cs);
  double secs;
  int i;
  int v = GetCPUCount(); //numero de particiones
  int N = atoi(argv[1]); //que mide el vector/* sólo lee correctamente hasta el tamaño máximo de int */
  int trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */

  for (i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */

  for (i=0; i<(v+1); i++) {
    printf("Trozo %d: %d\n",i,trozo[i]);
  }
 

  int tubo[v][2];
  for (size_t o = 0;o<v;o++)
	pipe(tubo[o]);
	
  
  int dato, estado, suma = 0;
 

  for (int j= 0; j<v; j++){
        gettimeofday(&t_ini, NULL);
	if (fork() == 0){
		CPU_SET(j, &cs);
		sched_setaffinity(0,sizeof(cs), &cs);
		close(tubo[j][0]);
		suma = 0;
		int k;
		
			
		for (k = trozo[j]; k<trozo[j+1]; k++){

			suma = suma + k;
		}
		write(tubo[j][1], &suma, sizeof(int));
		close(tubo[j][1]);

		gettimeofday(&t_fin, NULL);
		secs = timeval_diff(&t_fin, &t_ini);
		printf("Tiempo consumido por el proceso %d: %.16g milisegundos \n\n", (int)j, secs * 1000.0);
		//printf("Suma hijo numero %d: %d \n", j, suma);
		exit(0);
		
	}
	

  } 	
  
  int final = 0;

  for (int w=0; w<v;w++)
	wait(0);


  for (int z= 0; z<v;z++){
  	
	close(tubo[z][1]);
	
	while(read(tubo[z][0], &dato, sizeof(int)) > 0)
		final = final + dato;
	close(tubo[z][0]);
  }
  

  printf("La suma del padre es: %d \n", final);
  //final=0:
  exit(0);

}

