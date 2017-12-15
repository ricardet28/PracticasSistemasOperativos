/* aprox_eq N v ---> obtiene los números enteros, entre el 0 y el N, de manera que (en N) haya v regiones de tamaño similar */
/* el resultado se guarda en el vector trozo[] */
/* ejemplo: aprox_eq 8 2 devuelve 0 4 8 */
/* ejemplo: aprox_eq 8 3 devuelve 0 2 5 8 */

#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>

int main (int argc, char * argv[])
{ int i;
  int v = atoi(argv[2]);
  int N = atoi(argv[1]); /* sólo lee correctamente hasta el tamaño máximo de int */
  int trozo[v+1];
  double aux = (double) N/v; /* casting de tipos */

  for (i=0; i<(v+1); i++)
    trozo[i] = (int) (aux * i); /* casting de tipos */

  for (i=0; i<(v+1); i++) {
    printf("Trozo %d: %d\n",i,trozo[i]);
  }


  int t1[2]; //el 2 es para crearla, el 1 para escritura y el 0 para lectura
  pipe(t1);
  int dato, estado;
  int suma=0;

  if (fork()==0){//creamos primer hijo

    int suma= 0;
    int i=1;
    close(t1[0]);//cerramos lectura
    while(i<=trozo[1]){
	suma = suma + i;
	i = i+1;
    }
    write(t1[1], &suma, sizeof(suma));//escribimos la suma en el pipe
    close(t1[1]);//cerramos la escritura
    printf("Primer hijo: %d\n", suma);
    exit(0);




  }

  if (fork()==0){//creamos segundo hijo

    int suma= 0;
    int i=trozo[1] + 1;
    close(t1[0]);
    while(i<=trozo[2]){
	suma = suma + i;
	i = i+1;
    }
    write(t1[1], &suma, sizeof(suma));

    printf("Segundo hijo: %d\n", suma);
    exit(0);




  }


  wait(&estado);
  wait(&estado);


  close(t1[1]);
  while (read(t1[0], &dato, sizeof(int))>0)
	suma = suma + dato;
  close(t1[0]);
  printf("Total: %d\n", suma);
  exit(0);
}

