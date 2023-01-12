//
// Created by jiyun on 2023/01/07.
//

#include "minishell.h"

t_info g_info;

t_env	*new_env(char *key, char *value)
{
	t_env *node;

	node = malloc(sizeof(t_env) * 1);
	if (!node)
		return (NULL);
	node->key = key;
	node->value = value;
	node->next = NULL;
	return (node);
}

void	save_envs(char *envp[])
{
	t_env	*cur;
	t_env	*head;
	t_env	*tmp;
	char	**path;
	int		i;

	path = ft_split(envp[0], '=');
	cur = new_env(path[0], path[1]);
	head = cur;
	i = 1;
	while (envp[i] != NULL)
	{
		path = ft_split(envp[i], '=');
		tmp = new_env(path[0], path[1]);
		cur->next = tmp;
		cur = cur-> next;
		i++;
	}
	g_info.env_lst = head;
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

char	*join_three(char *start, char *end, char *middle)
{
	char *join_two;
	char *ret;

	join_two = ft_strjoin(start, middle);
	ret = ft_strjoin(join_two, end);
	return (ret);
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
		arr[i] = join_three(envs->key, envs->value, "=");
		envs = envs->next;
		i++;
	}
	arr[i] = 0;
	return (arr);
}

int main(int argc, char *argv[], char *envp[])
{
	t_cmd	*cmds;

	// signal 정의

	// 구조체 초기화

	// envp 정보화
	save_envs(envp);

	/* lst 잘 만들어졌는지 확인 */
	t_env *cur = g_info.env_lst;
	int i = 0;
	printf("========lst========\n");
	while (cur != NULL)
	{
		printf("lst %d: %s=%s\n", i++, cur->key, cur->value);
		cur = cur->next;
	}


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
