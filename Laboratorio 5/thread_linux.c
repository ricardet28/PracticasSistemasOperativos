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

#define MAX_THREADS 10

void *func(){

	printf("PID %d Thread %lu TaskID %ld \n", getpid(), pthread_self(), syscall(SYS_gettid));
	pthread_exit(0);


}

int main(){


	int i;
	pthread_t hilo[MAX_THREADS];

	printf("PID %d Thread %lu TaskID %ld \n\n", getpid(), pthread_self(), syscall(SYS_gettid));
	

	for (i = 0; i< MAX_THREADS; i++)
		pthread_create(&hilo[i], NULL, func, NULL);

	for (i = 0; i<MAX_THREADS; i++)
		pthread_join(hilo[i], NULL);
	exit(0);

}
