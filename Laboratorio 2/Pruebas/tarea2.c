#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>




int main(int argc, char * argv[]){


	int n = atoi(argv[1]);
	
	for (int i = 0; i<n; i++){
		
		int pid = fork();
		if (pid == 0){
			
			printf("proceso: %d con padre: %d\n", getpid(), getppid());
			//continue;
		}
		else{
			break;
		}
		


	
		
	}

	for (int i=0; i<n; i++){

		wait(0);
	}
	
	exit(0);





}
