#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
 #include <sys/time.h>

#define FNAME_SIZE 100
#define MAX_FILE_NO 10000
#define BLOCK_SIZE 1024

int main(int argc, char *argv[])
{
  int n, file_no;
  FILE *fp;
  char dest_file_name[FNAME_SIZE];
  char buf[BLOCK_SIZE];
  double time_taken;
  struct timeval  start,end;

  gettimeofday(&start, NULL);
  for(file_no=1;file_no<MAX_FILE_NO;file_no++)
  {
    fp = fopen("./files/foo1.pdf", "rb");
    if (fp == NULL) 
    {
      perror("Can't open dest file");
      exit(1);
    }
    
    bzero(buf,BLOCK_SIZE);
    while  ( (n = (int)fread( buf, 1, BLOCK_SIZE, fp )) > 0)
    {
      //do nothing with the read data;
      bzero(buf,BLOCK_SIZE);
    }

    fclose(fp);
  }

  gettimeofday(&end, NULL);

  time_taken = (double) ((end.tv_usec - start.tv_usec) / 1000000.0 + (double) (end.tv_sec - start.tv_sec));

  printf("\nTotal time take :  %f seconds \n", time_taken);
}

