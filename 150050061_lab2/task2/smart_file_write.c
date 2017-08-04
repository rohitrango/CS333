#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
	int fd = open("output.txt", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR);
	// printf("%d\n", fd);
	char *buf = "Hi I am the Parent\n";
	char *buf1 = "Hi I am the Child!\n";
	int w = write(fd, buf, strlen(buf));
	int pid = fork();
	if(pid == 0) {
		// its the child here
		w = write(fd, buf1, strlen(buf1));
	}
}
