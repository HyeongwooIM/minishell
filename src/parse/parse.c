//
// Created by jiyun on 2023/01/07.
//
#include "minishell.h"

t_info	g_info;

int	quote_closed(char *s)
{
	while (*s)
	{
		if (*s == '\"')
		{
			s += 1;
			while (*s != '\"')
			{
				if (*s == '\0')
					return (SYNTAX_Q);
				s++;
			}
		}
		else if (*s == '\'')
		{
			s += 1;
			while (*s != '\'')
			{
				if (*s == '\0')
					return (SYNTAX_Q);
				s++;
			}
		}
		s++;
	}
	return (SUCCESS);
}

int	input_tokenize(t_parse *info)
{
	if (just_white_space(info->input))
		return (RESTART);
	if (quote_closed(info->input) == SYNTAX_Q)
		return (SYNTAX_Q);
	make_chunk_lst(info);
	replace_chunk(info);
	if (make_token_lst(info) == SYNTAX_E)
		return (SYNTAX_E);
	return (SUCCESS);
}

void	error_handle(int error)
{
	if (error == SYNTAX_E)
		ft_putendl_fd("syntax error near unexpected token", STDOUT_FILENO);
	else if (error == SYNTAX_Q)
		ft_putendl_fd("syntax error near unclosed quote", STDOUT_FILENO);
}

void	free_info(t_parse *lst)
{
	free(lst->input);
	free_token_lst(lst->chunks);
	free_token_lst(lst->tokens);
}

void	parse(t_cmd **cmds)
{
	t_parse	info;
	int		error;

	info.input = readline("minishell$ ");
	if (!info.input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(g_info.last_exit_num);
	}
	if (*(info.input))
		add_history(info.input);
	info.chunks = NULL;
	info.tokens = NULL;
	error = input_tokenize(&info);
	if (error)
	{
		error_handle(error);
		free(info.input);
		free_token_lst(info.chunks);
		free_token_lst(info.tokens);
		return ;
	}
	make_cmd_lst(&info, cmds);
	free_info(&info);
}
