#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[])
{
	int n = atoi(argv[1]);
	int pid = fork();
	if(pid == 0) {
		// child process, close the stdout for it
		close(1);
		char *args[] = {"./my_head", (char*)argv[1], (char*)argv[2], NULL};
		int fd = open(argv[3], O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
		execv(args[0], args);
	}
	else {
		int ret = wait(&pid);
	}
	return 0;
}