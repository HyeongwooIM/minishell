#include "../minishell.h"

char *find_path(char *cmd, t_env *env, int *is_path)
{
	char **paths;
	char *part_path;
	char *path;
	int	i;

	while (env && ft_strcmp(env->key, "PATH"))
		env = env->next;
	if(!env)
	{
		*is_path = 0;
		return (0);
	}
	paths = ft_split(env->value, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if ((path, F_OK) == 0)
			return (path);
		free(path);
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
}