#include "../../includes/minishell.h"

int			get_dir(t_ms *ms)
{
	char		*pwd;
	if (ms->path[0] != 0)
	{
		//ft_strcpy(ms->old_path, ms->path);
		ft_bzero(ms->path, sizeof(ms->path));
	}
	if ((pwd = getcwd(NULL, 0)) == NULL)
		ft_putendl_fd("PWD error", 1);
	else
	{
		ft_putendl_fd(pwd, 1);
		//ms->old_path = ms->path;
		return (1);
	}
	return (0);
}

