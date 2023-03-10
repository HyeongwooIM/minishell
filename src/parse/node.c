/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 14:05:30 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:57:56 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(int type, char *word)
{
	t_token	*node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		ft_error_exit("malloc error", 1);
	node->type = type;
	node->word = ft_strdup(word);
	node->next = NULL;
	return (node);
}

t_rdir	*new_rdir(int type, char *with)
{
	t_rdir	*node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		ft_error_exit("malloc error", 1);
	node->type = type;
	node->here_doc_fd = 0;
	node->with = ft_strdup(with);
	node->next = NULL;
	return (node);
}

void	add_rdir_node(int type, char *with, t_rdir *rdir)
{
	t_rdir	*tmp;

	tmp = rdir;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new_rdir(type, with);
}

void	add_token_node(int type, char *word, t_token **tokens)
{
	t_token	*tmp;

	if (!*tokens)
		*tokens = new_token(type, word);
	else
	{
		tmp = *tokens;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_token(type, word);
	}
}
