#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

//int main() {
  
  

  //if (fork()!=0) /* I am the parent */
    //printf("Myselself: %d. My parent: %d\n", getpid(), getppid());
  //else      /* I am the child */
   // if (fork()!=0) /* I am the child, now parent */
      //printf("Myself: %d. My parent: %d\n", getpid(), getppid());
    //else      /* I am the child of the child */
      //printf("Myself: %d. My parent: %d\n", getpid(), getppid());
  //exit(0);
//}

//n = argc;




int main(){

	
	if (fork()!=0){
		printf("Myself: %d. My parent como padre: %d\n", getpid(), getppid());
		wait(0);
		
	}
	
	else      /* I am the child of the child */
		printf("Myself: %d. My parent como hijo: %d\n", getpid(), getppid());	
	


	
		
	
	exit(0);





}
