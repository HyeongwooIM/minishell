#include "../minishell.h"
#include "../libft/libft.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int get_size(t_env *envs)
{
	int	size;

	size = 0;
	while (envs != NULL)
	{
		envs = envs->next;
		size++;
	}
	return (size);
}

char	*join_with(char *a, char *b, char *c)
{
	char *str;
	size_t len; //size_t?
	size_t i;
	size_t j;

	if (!a || !b)
		return (0);
	len = ft_strlen(a) + ft_strlen(b) + ft_strlen(c);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(a))
	{
		str[i] = a[i];
		i++;
	}
	j = 0;
	while (j < ft_strlen(c))
	{
		str[i] = c[j];
		i++;
		j++;
	}
	j = 0;
	while (j < ft_strlen(b))
	{
		str[i]= b[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}


char	**lst_to_arr(t_env *envs)
{
	char **arr;
	// t_env *tmp;
	int size;
	int i;

	// tmp = envs;
	size = get_size(envs);
	arr = malloc(sizeof(char *) * size + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < size && envs != NULL)
	{
		arr[i] = join_with(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}


void	save_envs(char *envp[], t_env **envs)
{
	t_env	*cur;
	t_env	*tmp;
	char	**path;
	int		i;

	cur = malloc(sizeof(t_env) * 1);
	if (!cur)
		return ;
	*envs = cur;
	i = 0;
	while (envp[i] != NULL)
	{
		path = ft_split(envp[i], '=');
		cur->key = path[0];
		cur->value = path[1];
		tmp = malloc(sizeof(t_env) * 1);
		if (!tmp)
			return ;
		cur->next = tmp;
		cur = cur->next;
		i++;
	}
}

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

char **ft_strjoin2(char *str, char **arr)
{
	long	word_num;
	// long	word_len;
	long	i;
	char	**res;

	word_num = -1;
	while (arr[++word_num])
		;
	res = (char **)malloc(sizeof(char *) * (word_num + 2));
	if (!res)
		return (0); //error
	res[word_num + 1] = 0;
	// word_len = (long)ft_strlen(str);
	res[0] = ft_strdup(str);
	i = -1;
	while (++i < word_num)
		res[i + 1] = ft_strdup(arr[i]);
	return (res);
}

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

int main (int argc, char **argv, char **envp)
{
	t_cmd cmd;
	t_env *env;

	save_envs(envp, &env);
	if (argc && argv)
		;
	char	*content[5] = {"-al", 0};
	cmd.name = "ls";
	cmd.content = content;
	ft_exe(&cmd, env);
	return (0);
}