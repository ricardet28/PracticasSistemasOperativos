#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/syscall.h>

//#define MAX_THREADS 10


void *func(void *numero){
	
	int i;
	int valor = *((int *) numero);
	int factorial = 1;
	for (i=valor; i>0; i--){
		factorial = factorial * i;

	}

	printf("FACTORIAL DE %d = %d\n", valor, factorial);

	printf("PID %d Thread %lu TaskID %ld \n", getpid(), pthread_self(), syscall(SYS_gettid));
	pthread_exit(0);


}

int main(int argc, char * argv[]){
	
	printf("%dnumero:",argc);
	int amount = argc - 1;
	int vec[amount];
	
	for (int i=0; i<amount; i++){

		vec[i] = atoi(argv[i + 1]);
		//printf("%d ,", vec[i]);

	}
	
	int i;
	pthread_t hilo[amount];

	printf("PID %d Thread %lu TaskID %ld \n\n", getpid(), pthread_self(), syscall(SYS_gettid));
	

	for (i = 0; i< amount; i++)
		pthread_create(&hilo[i], NULL, func, (void *) &vec[i]);
		
	//ACTUA COMO WAIT
	for (i = 0; i<amount; i++){
		pthread_join(hilo[i], NULL);
		printf("Hilo %d finalizado. ", i);
	}
	exit(0);

}
