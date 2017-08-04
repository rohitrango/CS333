#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NUM "10"

int main(int argc, char *argv[])
{
	for(int i=1; i<argc; i++) {
		int pid = fork();
		if(pid == 0) {
			// this is the child, perform an exec
			char *margs[] = {"./my_head", NUM, argv[i], NULL};
			execv(margs[0], margs);
		}
		else {
			int ret = wait(&pid);
		}
	}
	return 0;
}