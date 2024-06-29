#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	
	int filedesm[2];
	int filedess[2];
	pid_t forkReturn = fork();
	int pipeReturnm = pipe(filedesm);
	int pipeReturns = pipe(filedess);
	
	if(pipeReturnm == -1)
	{
		printf("Pipe creation failed \n");
		exit(0);
	}
	if(pipeReturns == -1)
	{
		printf("Pipe creation failed \n");
		exit(0);
	}		
	if(forkReturn == -1)
	{
		printf("Fork creation failed \n");
		exit(0);
	}

	if(forkReturn)
	{
		printf("In wc main\n");
		close(filedess[1]);
		dup2(filedess[0],0);
		execlp("wc", "wc", "-l", NULL);	
	}
	if(!forkReturn)
	{
		pid_t childforkReturn = fork();
		if(childforkReturn == -1)
		{
			printf("Fork creation failed \n");
			exit(0);
		}	
		if(childforkReturn)
		{
			printf("In grep main\n");
			close(filedesm[1]);
			dup2(filedesm[0],0);
			close(filedess[0]);
			dup2(filedess[1],1);
			execlp("grep", "grep", "pts", NULL);
		}
		if(!childforkReturn)
		{
			printf("In ps main\n");
			close(filedesm[0]);
			dup2(filedesm[1], 1);
			execlp("ps", "ps", "-e", "-l", NULL);
		}
	}

}
