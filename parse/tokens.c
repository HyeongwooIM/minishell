//
// Created by jiyun on 2023/01/17.
//

#include "minishell.h"
#include "./parse.h"

t_token	*last_node(t_token *lst)
{
	t_token	*tmp;

	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

int	is_syntax_error(t_token *tokens)
{
	while (tokens)
	{
		if (tokens->type == NONE && tokens->next->type == PIPE)
			return (1);
		else if (tokens->type == PIPE && tokens->next == NULL)
			return (1);
		else if (tokens->type == REDIRECT && tokens->next->type != CHAR)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void    make_token_lst(t_token *chunks, t_token *tokens)
{
	//chunks -> CHAR CHAR PIPE ..
	int cmd_flag;

	cmd_flag = 0; // cmd가 아직 없음 cmd 생기면 1 되고 파이프를 만나면 다시 0 됨
	if (is_syntax_error(chunks))
		exit(1);
    while(chunks)
    {
		if (chunks->type == CHAR)
		{
			if (cmd_flag == 0)
			{
				chunks->type = CMD;
				cmd_flag = 1;
			}
			else
				chunks->type = OPTION;
		}
		else if (chunks->type == PIPE)
			cmd_flag = 0;
		add_token_node(chunks->type, chunks->word, last_node(tokens));
		chunks = chunks->next;
    }
}