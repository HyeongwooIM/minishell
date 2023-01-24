//
// Created by jiyun on 2023/01/17.
//

#include "minishell.h"
#include "./parse.h"

int	is_syntax_error(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == NONE && tokens->next->type == PIPE)
			return (1);
		else if (tokens->type == PIPE && tokens->next == NULL)
			return (1);
		else if (tokens->type == PIPE && tokens->next->type == PIPE)
			return (1);
		else if (tokens->type == REDIRECT && tokens->next->type != CHAR)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

int	make_token_lst(t_parse *info)
{
	//chunks -> CHAR CHAR PIPE ..
	t_token *chunks;
	int cmd_flag;
	int rdir_flag;

	chunks = info->chunks;
	cmd_flag = 0;
	rdir_flag = 0;
	if (is_syntax_error(info->chunks))
		return (FAIL);
    while(chunks)
    {
		if (chunks->type == CHAR)
		{
			if (cmd_flag == 0 && rdir_flag == 0)
			{
				chunks->type = CMD;
				cmd_flag = 1;
			}
			else if (rdir_flag == 1)
			{
				chunks->type = WITH;
				rdir_flag = 0;
			}
			else
				chunks->type = OPTION;
		}
		else if (chunks->type == PIPE)
			cmd_flag = 0;
		else if (chunks->type == REDIRECT)
			rdir_flag = 1;
		add_token_node(chunks->type, chunks->word, &info->tokens);
		chunks = chunks->next;
    }
	return (SUCCESS);
}