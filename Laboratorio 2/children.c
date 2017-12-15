#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
 
int main()
{
 
    int hijo1, hijo2;
    int nieto1, nieto2, nieto3, nieto4;
   
    //primer hijo del abuelo
    hijo1 = fork();
  if (hijo1 == 0)
  {
 
      nieto1 = fork();
    if(nieto1 != 0)
    {
        wait(0);
       
        nieto2 = fork();
        if(nieto2 != 0)
        {
            wait(0);
        }
        else
        {
              printf(" Soy nieto 2 Myselself: %d. My parent: %d\n", getpid(), getppid()); //nieto2
              exit(0);
        }
    }
    else
    {
        printf(" Soy nieto 1 Myselself: %d. My parent: %d\n", getpid(), getppid()); // nieto1
        exit(0);
    }
   
    printf(" Soy padre 1 Myself: %d. My parent: %d. Mis nietos: %d, %d\n", getpid(), getppid(), nieto1, nieto2);//padre1
    exit(0);
       
  }
  wait(0);
 
  //segundo hijo del abuelo
  hijo2 = fork();
  if (hijo2 == 0)
  {
 
    nieto3 = fork();
    if(nieto3 != 0)
    {
        wait(0);
       
        nieto4 = fork();
        if(nieto4 != 0)
        {
            wait(0);
        }
        else
        {
              printf(" Soy nieto 4 Myselself: %d. My parent: %d\n", getpid(), getppid()); //nieto2
              exit(0);
        }
    }
    else
    {
        printf(" Soy nieto 3 Myselself: %d. My parent: %d\n", getpid(), getppid()); // nieto1
        exit(0);
    }
        printf(" Soy padre 2 Myself: %d. My parent: %d. Mis nietos: %d, %d\n", getpid(), getppid(), nieto3, nieto4);//padre1
    exit(0);
       
  }
  wait(0);
 
    printf("Soy abuelo Myselself: %d. My parent: %d.  Mis nietos: %d, %d \n", getpid(), getppid(), hijo1, hijo2);
    exit(0);
}
