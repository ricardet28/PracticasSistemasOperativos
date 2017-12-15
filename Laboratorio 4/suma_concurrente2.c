#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sched.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/time.h>
#define MAX 20
 
 
double timeval_diff(struct timeval *a, struct timeval *b) {
  return
    (double)(a->tv_sec + (double)a->tv_usec/1000000) -
    (double)(b->tv_sec + (double)b->tv_usec/1000000);
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
 
int main()
{
    srand ( time(NULL) );
    struct timeval t_ini, t_fin;
    int v = GetCPUCount();
    cpu_set_t cs;
    CPU_ZERO(&cs);
    int dato, suma, estado = 0;
    int N = MAX;
    double secs;
    int trozo[v+1];
    int t[2];
    pipe(t);
    double aux = (double) N/v; /* casting de tipos */
 
    for (size_t i=0; i<(v+1); i++)
      trozo[i] = (int) (aux * i); /* casting de tipos */
 
    srand ( time(NULL) );
    int tubo[v][2];
    for (size_t i = 0; i < v; i++)
    {
      pipe(tubo[i]);
    }
 
    for (size_t i = 0; i < v; i++)
    {
      gettimeofday(&t_ini, NULL); /* obtiene tiempo inicial */
      if(fork() == 0)
      {
          CPU_SET(i,&cs);
          sched_setaffinity(0,sizeof(cs), &cs);
          ///close(tubo[i][0]);
	  close(t[0]);
          suma = 0;
          int j;
          for(j = trozo[i]; j < trozo[i + 1]; j ++)
          {
              suma = suma + j;
          }
 
          //write(tubo[i][1], &suma, sizeof(suma));
          //close(tubo[i][1]);
 	  write(t[1], &suma, sizeof(suma));
	  close(t[1]);
          gettimeofday(&t_fin, NULL); /* obtiene tiempo final */
 
            secs = timeval_diff(&t_fin, &t_ini); /* Obtiene el tiempo consumido */
            printf("Tiempo consumido por el proceso %d: %.16g milisegundos\n\n",(int)i, secs * 1000.0);
          exit(0);
      }
    }
 
    for (size_t i = 0; i < v; i++)
    {
      wait(0);
    }
    close(t[1]);
    
	
	suma = 0;
	while(read(t[0], &dato, sizeof(int)) > 0)
	  suma = suma + dato;

	close(t[0]);
 
    
 
    printf("La suma del padre es: %d \n",suma);
    exit(0);
 
}
