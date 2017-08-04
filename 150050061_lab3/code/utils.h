#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* check if there are redirects of the form ``{cmd} > {filename}'' */
int check_redirects(char **tokens) {
	
	int index = -1;
	for(int i = 0; tokens[i]!=NULL; i++)
		if(strcmp(tokens[i], ">") == 0)
			index = i;

	return index;
}

/* to check if there are multiple statements */
int* check_statements(char **tokens, int* c) {
	int count = 0, ii;
	int isLastColon = 0;
	for(ii = 0; tokens[ii]!=NULL; ii++) {
		if(strcmp(tokens[ii], ";;") == 0) {
			count++;
			isLastColon = 1;
		}
		else {
			isLastColon = 0;
		}
	}

	int *index;

	if(isLastColon==1)
		index = (int *)malloc(count * sizeof(int));
	else
		index = (int *)malloc((count+1) * sizeof(int));

	int t = 0;
	for(int i = 0; tokens[i]!=NULL; i++)
		if(strcmp(tokens[i], ";;") == 0) {
			index[t] = i;
			t++;
		}
	*c = count;
	if(isLastColon==0) {
		(*c)++;
		index[count] = ii;
	}
	return index;
}