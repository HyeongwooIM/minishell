//
// Created by jiyun on 2023/01/07.
//
#include "minishell.h"
#include "parse.h"

t_info g_info;

int	input_tokenize(t_parse *info)
{
	if (make_chunk_lst(info) == RESTART)
		return (FAIL);
	replace_chunk(info);
	if (make_token_lst(info) != SUCCESS)
	{
		ft_putstr_fd("syntax error\n", STDOUT_FILENO);
		return (FAIL);
	}
	return (SUCCESS);
}

void	init_parse_info(t_parse *info)
{
	info->chunks = NULL;
	info->tokens = NULL;
}

void    parse(t_cmd **cmds)
{
	t_parse info;

	info.input = readline("minishell$ ");
	if (!info.input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(g_info.last_exit_num);
	}
	if (*(info.input))
		add_history(info.input);
	init_parse_info(&info);
	if (input_tokenize(&info) == FAIL) {

		free(info.input);
		free_token_lst(info.chunks);
		free_token_lst(info.tokens);
		return ;
	}
	make_cmd_lst(&info, cmds);
}
