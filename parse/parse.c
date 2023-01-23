//
// Created by jiyun on 2023/01/07.
//

// " ", ' ', $ 치환
// input token화
// token으로 실행부로 옮길 구조체 완성하기

#include "minishell.h"
#include "parse.h"

t_info g_info;

int	input_tokenize(t_parse *info)
{
	if (make_chunk_lst(info) != SUCCESS)
		return (FAIL);
	replace_chunk(info);
	if (make_token_lst(info) != SUCCESS)
		return (FAIL);
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

	// 1. 공백만 파싱 선에서 다시 실행
	// 2. 토큰화 실패(malloc 외, 공백문자만 있다던지..)도 파싱 선에서 다시 실행
	// 3. 넘겨줄 데이터 구조체 채우기 실패까지 파싱 선에서 다시 실행
	info.input = readline("minishell$ ");
	if (!info.input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(g_info.last_exit_num);
	}
	if (!*(info.input))
		add_history(info.input);
	init_parse_info(&info);
	if (input_tokenize(&info) == FAIL) {

		free(info.input);
		free_token_lst(info.chunks);
		free_token_lst(info.tokens);
		ft_putstr_fd("syntax error\n", STDOUT_FILENO);
		return ;
	}
	make_cmd_lst(&info, cmds);
}
