#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define ARRAY_SIZE 2000000

int main()
{
	int array[ARRAY_SIZE];
	int i;

	printf("\n\nProgram : 'memory_4'\n");
	printf("____________________\n");
	printf ("\n\nPID : %d \n",getpid());
	printf( "Size of int : %ld \n",sizeof(int));

	for(i=0;i<ARRAY_SIZE/2;i++)
	{
		array[i] = 10;
	}

	for(i=1;i<ARRAY_SIZE/2;i++)
	{
		array[i] = array[i-1]+25;
	}


	printf("\nPress Enter Key to exit.\n");

	getchar();    
	return 0;
}

