#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define STDOUT 1

int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]); 
	int fd = open(argv[2], O_RDONLY);
	char *buf = malloc(n);
	read(fd, buf, n);
	write(STDOUT, buf, n);
	close(fd);
	free(buf);
}
