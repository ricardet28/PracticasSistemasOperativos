#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>




int main(){
	
	pid_t abuelo = getpid();
	
	printf("ABUELO = %d\n", abuelo);
	//int n = atoi(argv[1]);
	
	//pid_t pid = fork();
	
	if (fork()==0){
		pid_t padre1 = getpid();
		//pid_t pid2 = fork();
		printf("soy %d y mi padre es %d\n", padre1, abuelo);
		if (fork()== 0){
			pid_t hijo1 = getpid();
			printf("soy %d y mi padre es %d\n", hijo1, padre1);
			exit(0);
		}
		
			
		//pid_t pid3 = fork();
		if (fork() == 0){
			pid_t hijo2 = getpid();
			printf("soy %d y mi padre es %d\n", hijo2, padre1);
			exit(0);
		}
		wait(0);
		wait(0);
		exit(0);
		
	}
	

	//pid_t anotherPid = fork();
	
	if (fork() == 0){

		pid_t padre2 = getpid();
		printf("soy %d y mi padre es %d\n", padre2, abuelo);
		//pid_t anotherPid2 = fork();
		if (fork() == 0){
			pid_t hijo3 = getpid();
			printf("soy %d y mi padre es %d\n", hijo3, padre2);
			exit(0);
		}
		
		//pid_t anotherPid3 = fork();
		if (fork() == 0){
			pid_t hijo4 = getpid();
			printf("soy %d y mi padre es %d\n", hijo4, padre2);
			exit(0);
		}
		wait(0);
		wait(0);
		exit(0);

	}
	wait(0);
	wait(0);

	exit(0);




}
