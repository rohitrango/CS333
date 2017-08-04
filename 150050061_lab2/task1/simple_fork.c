#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
	int pid = fork();
	if(pid != 0) {
		printf("Parent: The child’s process ID is : %d\n", pid);
		int ret = wait(&pid);
		printf("Parent: The child has terminated.\n");
	}
	else {
		printf("Child: The child’s process ID is : %d\n", getpid());
	}


}
