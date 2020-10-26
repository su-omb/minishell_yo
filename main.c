#include <stdio.h>
#include <unistd.h>



int			main()
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
}