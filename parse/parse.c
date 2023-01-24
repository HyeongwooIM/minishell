//
// Created by jiyun on 2023/01/07.
//
#include "includes/minishell.h"

t_info g_info;

int quote_closed(char *s)
{
	int d_quote_on;
	int s_quote_on;

	d_quote_on = FALSE;
	s_quote_on = FALSE;
	while (*s)
	{
		if (*s == '\"')
			d_quote_on = !d_quote_on;
		else if (*s == '\'')
			s_quote_on = !s_quote_on;
		s++;
	}
	if (d_quote_on == TRUE || s_quote_on == TRUE)
		return (SYNTAX_Q);
	return (SUCCESS);
}

int	input_tokenize(t_parse *info)
{
	if (just_white_space(info->input))
		return (RESTART);
	if(quote_closed(info->input) == SYNTAX_Q)
		return (SYNTAX_Q);
	make_chunk_lst(info);
	replace_chunk(info);
	if (make_token_lst(info) == SYNTAX_E)
        return (SYNTAX_E);
	free_token_lst(info->chunks);
	return (SUCCESS);
}

void	init_parse_info(t_parse *info)
{
	info->chunks = NULL;
	info->tokens = NULL;
}

void	error_handle(int error)
{
	if (error == SYNTAX_E)
		ft_putendl_fd("syntax error near unexpected token\n", 258);
	else if (error == SYNTAX_Q)
		ft_putendl_fd("syntax error near unclosed quote\n", 257);
}

void    parse(t_cmd **cmds)
{
	t_parse info;
	int error;

	info.input = readline("minishell$ ");
	if (!info.input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(g_info.last_exit_num);
	}
	if (*(info.input))
		add_history(info.input);
	init_parse_info(&info);
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
}
