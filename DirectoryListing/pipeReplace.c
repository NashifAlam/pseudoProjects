#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
int main()
{
	int p[2];
	if(pipe(p) == -1)
		printf("creation of pipe failed\n");
	
	int retFork= fork();
	if(retFork == -1)
		printf("creation of fork failed\n");

	if(!retFork)
	{
		char buff[100];
		printf("In child process PID = %d PPID = %d\n", getpid(), getppid());
		close(p[1]);
		while(1){
		read(p[0],buff,sizeof(buff));
		for(int i = 0;buff[i] != '\0'; ++i)
			if(islower(buff[i]))
				buff[i] = toupper(buff[i]);

		printf("%s\n", buff );}
	}
	else
	{
		char readBuff[100];
		close(p[0]);
		printf("In parent process PID = %d PPID = %d\n", getpid(), getppid());
		while(1)
		{	
			printf("Enter Data\n");
			scanf("%s", readBuff);
			write(p[1], readBuff, strlen(readBuff)+1);
		}
	}
}
