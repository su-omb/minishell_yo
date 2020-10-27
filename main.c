#include <stdio.h>
#include <unistd.h>
#include <string.h>



/* int			main()
{
	char	*pwd;
	if ((pwd = getcwd(NULL, 0)) == NULL)
	{
        perror("Error");
	}
	else
	{
		printf("%s\n", pwd);
		return (0);
	}

	return (1);
} */

int main(int ac, char **av)
{
	char *path;

	if (strcmp(av[0], "cd"))
	{
		strcpy(path, av[1]);
		

	}

}

