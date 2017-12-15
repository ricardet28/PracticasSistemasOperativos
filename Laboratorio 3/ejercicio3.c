#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char * argv[]){

	int contador=0;
	int dato;
	int testigo = 1;
	int iteraciones = atoi(argv[1]);
	int t1[2], t2[2], t3[2];
	
	pipe(t1);
	pipe(t2);
	pipe(t3);
	
	int i=1;
	
	write(t3[1], &testigo, sizeof(testigo));
	



	if (fork()==0){//lee de 3 y escribe en 1


		testigo = 2;
		close(t1[0]);
		close(t2[0]);
		close(t2[1]);
		close(t3[1]);

		while (read (t3[0], &dato, sizeof(dato))>0){

			if (dato==1){
				int pid = getpid();
				printf("proceso 1: %d \n", pid); 
				write(t1[1], &testigo, sizeof(testigo));
				contador++;
				
			}
			if (contador == iteraciones){

				exit(0);

			}
		}
		
		
		
              
		
	}

	if (fork()==0){//lee de 1 y escribe en 2
		testigo = 3;
		close(t1[1]);
		close(t2[0]);
		
		close(t3[1]);
		close(t3[0]);
		while (read (t1[0], &dato, sizeof(dato))>0){

			if (dato==2){
				int pid = getpid();
				printf("proceso 2: %d \n", pid); 
				write(t2[1], &testigo, sizeof(testigo));
				contador++;
				
			}
			if (contador == iteraciones){

				exit(0);

			}
		}
		
		
	}

	if (fork()==0){//lee de 2 y escribe en 3
		testigo = 1;
		close(t1[0]);
		close(t1[1]);
		
		close(t2[1]);
		close(t3[0]);
		while (read (t2[0], &dato, sizeof(dato))>0){

			if (dato==3){
				int pid = getpid();
				printf("proceso 3: %d \n", pid); 
				write(t3[1], &testigo, sizeof(testigo));
				contador++;
				
			}
			if (contador == iteraciones){

				exit(0);

			}
		}
		
		
	}
	wait(0);
	wait(0);
	wait(0);







}
