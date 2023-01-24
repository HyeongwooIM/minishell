//
// Created by jiyun on 2023/01/19.
//

#include "includes/minishell.h"

void	add_name(t_token *token, t_cmd *cmds)
{
	cmds->name = token->word;
}

void	add_content(t_token *token, t_cmd *cmds)
{
	if (!cmds->content)
	{
		cmds->content = malloc(sizeof(char *) * 2);
		if(!cmds->content)
			ft_error_exit("malloc error\n", 1);
		(cmds->content)[0] = ft_strdup(token->word);
		(cmds->content)[1] = 0;
	}
	else
		cmds->content = ft_strjoin_1to2(cmds->content, token->word);
}

void	add_rdir(t_token *token, t_cmd *cmds)
{
	if (ft_strcmp(token->word, ">") == 0)
		token->type = RDIR;
	else if (ft_strcmp(token->word, "<") == 0)
		token->type = R_RDIR;
	else if (ft_strcmp(token->word, ">>") == 0)
		token->type = D_RDIR;
	else
	{
		token->type = HEREDOC;
		cmds->is_heredoc = 1;
	}
	if (cmds->rdir == NULL)
		cmds->rdir = new_rdir(token->type, token->next->word);
	else
		add_rdir_node(token->type, token->next->word, cmds->rdir);
}

void make_cmd_lst(t_parse *info, t_cmd **cmds)
{
	t_token *tmp_t;
	t_cmd *tmp_c;

	tmp_t = info->tokens;
	*cmds = init_cmd();
	tmp_c = *cmds;
	while (tmp_t)
	{
		if (tmp_t->type == CMD)
			add_name(tmp_t, tmp_c);
		else if (tmp_t->type == OPTION)
			add_content(tmp_t, tmp_c);
		else if (tmp_t->type == REDIRECT)
		{
			add_rdir(tmp_t, tmp_c);
			tmp_t = tmp_t->next;
		}
		else if (tmp_t->type == PIPE)
		{
			tmp_c->next = init_cmd();
			tmp_c = tmp_c->next;
		}
		tmp_t = tmp_t->next;
	}
}