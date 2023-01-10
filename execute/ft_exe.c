#include "../minishell.h"

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;
	int		i;
	char	*part_path;

	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (0);
}

char *fint_path(char *cmd)
{
	t_env *temp;
	char **paths;
	char *part_path;
	char *path;
	int	i;

	temp = &g_env;
	while (!ft_strcmp(temp->key, "PATH"))
		temp = temp->next;
	paths = ft_split(temp->value, ':');
	i = -1;
	while (paths[++i])
	{
		part_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(part_path, cmd);
		free(part_path);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
	}
	return (0); //error?
}

void ft_exe(t_cmd *cmd)
{
	char	**content;
	char	*path;
	char 	**paths;
	int		i;
	char	**envp;

	path = get_path(cmd->name);
	content = ft_strjoin2(path, cmd->content);
	i = -1;
	if (!path)
	{
		while (content[++i])
			free(content[i]);
		free(content);
		//error_exit("cmd not found");
	}
	envp = lst_to_arr(&g_env);
	if (execve(path, cmd, envp) == -1)
		error_exit("exeve error");
}