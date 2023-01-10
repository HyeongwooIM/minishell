#include "../minishell.h"

char *find_path(char *cmd, t_env *env)
{
	t_env *temp;
	char **paths;
	char *part_path;
	char *path;
	int	i;

	temp = env;
	while (ft_strcmp(temp->key, "PATH"))
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

void ft_exe(t_cmd *cmd, t_env *env)
{
	char	**content;
	char	*path;
	int		i;
	char	**envp;

	path = find_path(cmd->name, env);
	content = ft_strjoin2(path, cmd->content);
	i = -1;
	if (!path)
	{
		while (content[++i])
			free(content[i]);
		free(content);
		//error_exit("cmd not found");
	}
	envp = lst_to_arr(env);
	if (execve(path, content, envp) == -1)
		// error_exit("exeve error");
		;
}