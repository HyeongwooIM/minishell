//
// Created by jiyun on 2023/01/17.
//

#include "../minishell.h"
#include "parse.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || \
			c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
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

t_token	*new_token(int type, char *word)
{
	t_token *node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		exit(1);
	node->type = type;
	node->word = word;
	node->next = NULL;
	return (node);
}

void	add_node(int type, char *word, t_token *head)
{
	if (head->word == NULL)
	{
		head->type = type;
		head->word = word;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_token(type, word);
	}
}