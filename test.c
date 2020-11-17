#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/wait.h>

int		main()
{
	pid_t	pid;
	int		fd;
	int		st = 0;
	char	*args[] = { "ls", "-l", "-a", (char *)0 };
    char	*env_args[] = { "PATH=/bin", (char*)0 };

	pid = fork();
	if (pid == 0)
	{
		fd = open("txt", O_WRONLY);
		dup2(fd, 1);
		execve(args[0], args, env_args);
	}
	else if (pid < 0)
		printf("Error fork\n");
	waitpid(pid, &st, 0);
}