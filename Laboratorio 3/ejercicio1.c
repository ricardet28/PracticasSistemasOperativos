#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <fcntl.h>

#include <stdlib.h>

int main(){

	char dato;
	int fd;
	fd = open("VelesEVents", O_RDONLY);
	while (read(fd, &dato, sizeof(char))>0)
		printf("%c", dato);
	close(fd);
	exit(0);



}
