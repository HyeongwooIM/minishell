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

int just_white_space(char *str)
{
	while (*str)
	{
		if (!is_space(*str))
			return (0);
		str++;
	}
	return (1);
}

t_token	*init_token()
{
	t_token *ret;

	ret = malloc(sizeof(t_token) * 1);
	if (!ret)
		ft_error_exit("malloc error", 1);;
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
		ft_error_exit("malloc error", 1);;
	ret->name = NULL;
	ret->content = NULL;
	ret->rdir = NULL;
	ret->is_heredoc = 0;
	ret->next = NULL;
	return (ret);
}