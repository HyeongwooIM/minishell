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

/* 추후 refactoring에 필요
int	cpy_str(char *dest, const char *src, size_t dstsize)
{
	int	i;
	int	src_len;

	i = 0;
	src_len = ft_strlen(src);
	if (dstsize == 0)
		return (src_len);
	while (src[i] != '\0' && i + 1 < dstsize)
	{
		dest[i] = src[i];
		i++;
	}
	return (src_len);
}
*/

char	*join_with(char *a, char *b, char *c)
{
	char *str;
	int len; //size_t?
	int i;
	int j;

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

char	**lst_to_arr(t_env *envs)
{
	char **arr;
	t_env *tmp;
	int size;
	int i;

	tmp = envs;
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

int main(int argc, char *argv[], char *envp[])
{
	t_env	*envs;
	// signal 정의

	// envp 정보화
	save_envs(envp, &envs);

	/* lst 잘 만들어졌는지 확인
	printf("========lst========\n");
	int size = 0;
	while (envs != NULL)
	{
		printf("%s: %s\n", envs->key, envs->value);
		envs = envs->next;
		size++;
	}
	printf("lst size: %d\n", size);
	*/

	/* lst_to_arr 함수 확인
	char **arr = lst_to_arr(envs);
	printf("========arr========\n");
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
	*/

	while (1)
	{
		// parse
		// execute
	}
	// free
}
