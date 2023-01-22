#include "minishell.h"

char *no_path(char *cmd)
{
	struct stat buf;

	if (stat(cmd, &buf) == 0) //succes = 0 fail, error = -1
	{
		if ((buf.st_mode & S_IFMT) == S_IFDIR)
			ft_error_exit("is a directory", 1);
		return (cmd);
	}
	ft_putstr_fd(cmd, 1);
	ft_error_exit("No such file or directory",1);
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
		if (!part_path)
			ft_error_exit("malloc error", 1);
		path = ft_strjoin(part_path, cmd);
		if (!path)
			ft_error_exit("malloc error", 1);
		free(part_path);
		if (stat(path, &buf) == 0)
		{
			if ((buf.st_mode & S_IFMT) == S_IFDIR)
			{
				ft_putstr_fd(path, 2);
				ft_putstr_fd("is a directory", 1);
			}
			return (path);
		}
		free(path);
	}
	return (0);
	// ft_putstr_fd(cmd, 2);
	// ft_error_exit("Command not found", 127);
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
		*is_path = 1;
		return (yes_path(cmd, env));
	}
	return (0); //error?
}

void ft_exe(t_cmd *cmd, t_env *env)
{
	char	**content;
	char	*path;
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
			{
				ft_putstr_fd(cmd->name, 2);
				ft_error_exit("No such file or directory", 1);
			}
		}
	}
	content = ft_strjoin2(path, cmd->content);
	envp = lst_to_arr(env);
	(execve(path, content, envp) == -1);
		ft_error_exit("Command not found", 127);
}