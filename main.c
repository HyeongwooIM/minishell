//
// Created by jiyun on 2023/01/07.
//

#include "minishell.h"

t_env g_env;

void	save_envs(char *envp[], t_env **envs)
{
	t_env	*cur;
	t_env	*tmp;
	char	**path;
	int		i;

	cur = malloc(sizeof(t_env) * 1);
	if (!tmp)
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

char	*join_with(char *a, char *b, char *c)
{
	char *str;
	int len; //size_t?
	int i;
	int j;

	len = ft_strlen(a) + ft_strlen(b) + ft_strlen(c);
	str = malloc(sizeof(char) * len + 1);
	if (!str)
		return ;
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
	t_env *tmp;
	int size;
	int i;

	tmp = envs;
	size = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		size++;
	}
	arr = malloc(sizeof(char *) * size + 1);
	if (!arr)
		return ;
	i = 0;
	while (i < size)
	{
		arr[i] = join_with(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int main(int argc, char *argv[], char *envp[])
{
	t_env	*envs;
	// signal 정의
	// envp 정보화
	save_envs(envp, &envs);
	// parse
	// execute
	// free
}