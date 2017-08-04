#include <stdio.h>       
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void catch_error(int sig) {
	if (sig == SIGINT) {
		printf("Do you really want to quit (y|n)?\n");
		char ch = getchar();
		if(ch == 'y')
			exit(0);
	}
}

int main(int argc, char const *argv[])
{
	signal(SIGINT, catch_error);
	while(1){}	
}