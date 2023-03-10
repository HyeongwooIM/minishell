/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:05:42 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:58:36 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_syntax_error(t_token *tokens)
{
	if (tokens->type == PIPE)
		return (1);
	while (tokens)
	{
		if (tokens->type == REDIRECT && \
		(tokens->next == NULL || tokens->next->type != CHAR))
			return (1);
		else if (tokens->type == PIPE && tokens->next == NULL)
			return (1);
		else if (tokens->type == PIPE && tokens->next->type == PIPE)
			return (1);
		tokens = tokens->next;
	}
	return (0);
}

void	char_to_what(t_token *chunks, int *cmd_flag, int *rdir_flag)
{
	if (*cmd_flag == 0 && *rdir_flag == 0)
	{
		chunks->type = CMD;
		*cmd_flag = 1;
	}
	else if (*rdir_flag == 1)
	{
		chunks->type = WITH;
		*rdir_flag = 0;
	}
	else
		chunks->type = OPTION;
}

int	make_token_lst(t_parse *info)
{
	t_token	*chunks;
	int		cmd_flag;
	int		rdir_flag;

	chunks = info->chunks;
	cmd_flag = 0;
	rdir_flag = 0;
	if (is_syntax_error(info->chunks))
		return (SYNTAX_E);
	while (chunks)
	{
		if (chunks->type == CHAR)
			char_to_what(chunks, &cmd_flag, &rdir_flag);
		else if (chunks->type == PIPE)
			cmd_flag = 0;
		else if (chunks->type == REDIRECT)
			rdir_flag = 1;
		add_token_node(chunks->type, chunks->word, &info->tokens);
		chunks = chunks->next;
	}
	return (SUCCESS);
}
