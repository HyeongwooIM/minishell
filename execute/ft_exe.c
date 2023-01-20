#include "../minishell.h"
#include <sys/stat.h>

char *no_path(char *cmd)
{
	struct stat buf;

	if (stat(cmd, &buf) == 0) //succes = 0 fail, error = -1
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
			ft_putstr_fd("is a directory", 1);
		return (cmd);
	}
	ft_putstr_fd("No such file or directory",1); // error;
	exit(1); // error
}

char *yes_path(char *cmd, t_env *env)
{
	char		*part_path;
	char		*path;
	char		**paths;
	struct stat buf;
	int			i;

	paths = ft_split(env->value, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (stat(path, &buf) == 0)
		{
			if ((buf.st_mode & S_IFMT) == S_IFDIR)
				ft_putstr_fd("is a directory", 1);
			return (path);
		}
		free(path);
	}
	ft_putstr_fd("Command not found",1); // error;
	exit(1); // error
}

char *find_path(char *cmd, t_env *env, int *is_path)
{
	int	i;
	
	*is_path = 0;
	env = find_env("PATH");
	if(!env)
		return (no_path(cmd));
	else
	{
		is_path = 1;
		return (yes_path(cmd, env));
	}
	return (0); //error?
}

void ft_exe(t_cmd *cmd, t_env *env)
{
	char	**content;
	char	*path;
	int		i;
	char	**envp;
	int		is_path;

	path = find_path(cmd->name, env, &is_path);
	if (!path)
	{
		if(!is_path)
		{
			path = cmd->name;
			content = ft_strjoin2(path, cmd->content);
			envp = lst_to_arr(env);
			if (execve(path, content, envp) == -1)
				printf("No such file or directory");
		}
	}
	content = ft_strjoin2(path, cmd->content);
	envp = lst_to_arr(env);
	(execve(path, content, envp) == -1);
	ft_putstr_fd("Command not found",1);
}

// 폴더인지확인