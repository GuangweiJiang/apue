#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE		2048

int 
main(void)
{
	char	buf[MAXLINE];	
	pid_t	pid;
	int		status;

	printf("%% ");	/* printf prompt (print requires %% to print %) */
	while (fgets(buf, MAXLINE, stdin) != NULL)
	{
		if (buf[strlen(buf) - 1] == '\n')
			buf[strlen(buf) - 1] = 0;	/* replace newline with null */

		if ((pid = fork() < 0))
		{
			printf("fork error\n");
		}
		else if (pid == 0)
		{
			execlp(buf, buf, (char *)0);
			//printf("couldn't execute: %s\n", buf);
			//exit(127);
		}

		/* parent */
		if ((pid = waitpid(pid, &status, 0)) < 0)
			printf("waitpid error\n");

		printf("%% ");
	}
	exit(0);
}
