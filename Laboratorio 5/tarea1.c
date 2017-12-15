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
	
	int a = atoi(argv[1]);
	int b = atoi(argv[2]);
	
	int vec[2];
	vec[0] = a;
	vec[1] = b;
		
	
	int i;
	pthread_t hilo[2];

	printf("PID %d Thread %lu TaskID %ld \n\n", getpid(), pthread_self(), syscall(SYS_gettid));
	

	for (i = 0; i< 2; i++)SSS
		pthread_create(&hilo[i], NULL, func, (void *) &vec[i]);
		
	//ACTUA COMO WAIT
	for (i = 0; i<2; i++)
		pthread_join(hilo[i], NULL);
	exit(0);

}
