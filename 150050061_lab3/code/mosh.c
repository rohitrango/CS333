#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>

#include "make-tokens.h"
#include "utils.h"

#define CWD_LEN 1024
#define STDOUT 1

int main(int argc, char const *argv[])
{
	// Variables here
	char cmd[MAX_INPUT_SIZE];
	
	// char path[CWD_LEN];
	// for the loop
	char **tokens;
	int tokenCount;

	// variables for redirection
	int redirectIndex;
	char **firstCommand, *mFile;

	// variables for statements
	int *rIndices;
	int rCount;


	// variables for the main command
	char **loopTokens;
	int loopTokenCount;

	while(1) {

		// get current path, uncomment the first one
		// bzero(path, CWD_LEN);
		// getcwd(path, CWD_LEN);
		// printf("mosh:%s> ", path);
		printf("mosh> ");

		/* make cmd blank and take input */
		bzero(cmd, MAX_INPUT_SIZE);
        gets(cmd);
        cmd[strlen(cmd)] = '\n';  		
        
        /* get tokens and tokenCount */
		loopTokens = tokenize(cmd);
		loopTokenCount = 0;
		for(loopTokenCount=0;loopTokens[loopTokenCount]!=NULL; loopTokenCount++);

		// continue if no tokens
		if(loopTokenCount == 0)
			continue;

		/*
			Here we will have code which makes the tokens separated, and then we perform the operations.
			If one operation fails, we must ideally abort the rest.
			Make the tokens permanent
		*/
		rIndices = check_statements(loopTokens, &rCount);
		int start = 0, end;
		for(int i=0; i<rCount; i++) {
			// take from start to end, and copy all the strings
			end = rIndices[i];
			tokenCount = end-start;
			tokens = (char **)malloc((tokenCount+1) * sizeof(char *));
			for(int j = 0; j<tokenCount; j++) {
				tokens[j] = (char *)malloc(strlen(loopTokens[start+j]) * sizeof(char));
				strcpy(tokens[j], loopTokens[start+j]);
			}
			tokens[tokenCount] = NULL;

			start = end+1;

			/*
				Here we have the tokens, and the count.
				Apply the recursion on this whole thing
			*/

			/* check for chdir */
			if(strcmp(tokens[0], "cd") == 0) {

				// for cd, we have to use chdir 
				// find directory, if not, go to home directory
				if(tokenCount > 2)
					printf("%s\n", "Error: Invalid number of arguments. Format: cd <dir_name>");
				else {
					int chd;
					if(tokenCount != 1)
						chd = chdir(tokens[1]);
					else
						chd = chdir(getenv("HOME"));
						
					if(chd == -1) 
						printf("%s\n", "Error: No such directory.");
				}
			}

			/* check if there are redirects */
			else if((redirectIndex = check_redirects(tokens)) != -1) {
				if(redirectIndex == tokenCount-1) {
					printf("%s\n", "Error: Invalid format.");
				}
				else {
					// initialize the firstCommand and mFile variables
					firstCommand = (char **)malloc((redirectIndex+1) * sizeof(char *));
					mFile = (char *)malloc(strlen(tokens[redirectIndex+1]) * sizeof(char));
					
					// copy filename and cmd
					strcpy(mFile, tokens[redirectIndex+1]);
					for(int i=0; i<redirectIndex; i++) {
						firstCommand[i] = (char *)malloc(strlen(tokens[i]) * sizeof(char));
						strcpy(firstCommand[i], tokens[i]);
					}
					firstCommand[redirectIndex] = NULL;

					// fork a new process and change its fd
					int pid = fork();
					if(pid == 0) {
						int fd = open(mFile, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH);
						if(fd < 0) {
							printf("%s\n", "Error: Cannot write to file.");
						}
						else {
							if(dup2(fd, 1) < 0){
								printf("%s\n", "Some error.");
							}
							else {
								execvp(firstCommand[0], firstCommand);
								close(fd);
							}
							return 0;
						}
					}
					else {
						int st = wait(&pid);
					}

				}
			}

			/* consider all the other functions which can be Linux system commands */
			else {
				// pass it to bash
				int pid = fork();
				if(pid == 0) {
					execvp(tokens[0], tokens);
					return 0;
				}
				else {
					int st = wait(&pid);
				}
			}



		// end of for loop for the ;; statements
		}
		
	}
	return 0;
}




