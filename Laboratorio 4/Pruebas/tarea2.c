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
#include <sys/resource.h>
#include <sched.h>



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

int main (int argc, char * argv[])
{

  int i;
  int tubo[2];
  pipe(tubo);

  int v = GetCPUCount(); //numero de cachos en los que hacer la suma
  int sumasParciales[2];
  int N = atoi(argv[1]); //num a sumar todos sus num anteriores
  int trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */

  for (i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */

  for (i=0; i<(v+1); i++)
    printf("Trozo %d: %d\n",i,trozo[i]);


  for (int i=0;i<v; i++){


    int sumaParcial = 0;
    if (fork()==0){
        close(tubo[0]);
        for (int j=trozo[i]; j<trozo[i+1]; j++){
            sumaParcial = sumaParcial +(j+1);
        }
        //printf("hola");
        write(tubo[1], &sumaParcial, sizeof(sumaParcial));
        printf("La suma parcial desde %d hasta %d es: %d\n", trozo[i] + 1, trozo[i+1], sumaParcial);
        close(tubo[1]);

        exit(0);
    }




  }

  for (int i=0; i<v; i++){

      wait(0);

  }
  close(tubo[1]);
  int sumaTotal = 0;
  int dato;
  while(read(tubo[0], &dato, sizeof(int))>0)
    sumaTotal += dato;
  printf("La suma total es: %d\n",sumaTotal);
  exit(0);


}
