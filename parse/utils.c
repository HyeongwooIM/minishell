//
// Created by jiyun on 2023/01/17.
//

#include "minishell.h"
#include "parse.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || \
			c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

//int	ft_strcmp(const char *str1, const char *str2)
//{
//	while (*str1 || *str2)
//	{
//		if (*str1 != *str2)
//			return (*str1 - *str2);
//		str1++;
//		str2++;
//	}
//	return (*str1 - *str2);
//}

t_token	*init_token()
{
	t_token *ret;

	ret = malloc(sizeof(t_token) * 1);
	if (!ret)
		exit(1);
	ret->type = NONE;
	ret->word = NULL;
	ret->next = NULL;
	return (ret);
}

t_cmd	*init_cmd()
{
	t_cmd *ret;

	ret = malloc(sizeof(t_cmd) * 1);
	if (!ret)
		exit(1);
	ret->name = NULL;
	ret->content = NULL;
	ret->rdir = NULL;
	ret->is_heredoc = NONE;
	ret->next = NULL;
	return (ret);
}

t_token	*new_token(int type, char *word)
{
	t_token *node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		exit(1);
	node->type = type;
	node->word = ft_strdup(word);
	node->next = NULL;
	return (node);
}

t_rdir	*new_rdir(int type, char *with)
{
	t_rdir *node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		exit(1);
	node->type = type;
	node->here_doc_fd = 0;
	node->with = ft_strdup(with);
	node->next = NULL;
	return (node);
}

void	add_rdir_node(int type, char *with, t_rdir *rdir)
{
	t_rdir *tmp;

	tmp = rdir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_rdir(type, with);
}

void	add_token_node(int type, char *word, t_token *tokens)
{
	t_token *tmp;

	tmp = tokens;
	if (tmp->type == NONE)
	{
		tmp->type = type;
		tmp->word = word;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token(type, word);
	}
}