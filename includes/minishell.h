/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: him <him@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 17:54:39 by him               #+#    #+#             */
/*   Updated: 2023/01/27 17:54:41 by him              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PATH_MAX 4096

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <termios.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"
# include "execute.h"
# include "parse.h"

typedef enum e_chunk_type
{
	NONE = -42,
	CHAR,
	REDIRECT,
	PIPE
}	t_chunk_type;

typedef enum e_token_type
{
	CMD = -24,
	OPTION,
	WITH
}	t_token_type;

typedef enum e_rdir_type
{
	RDIR,
	R_RDIR,
	D_RDIR,
	HEREDOC
}	t_rdir_type;

typedef struct s_token
{
	int				type;
	char			*word;
	struct s_token	*next;
}	t_token;

typedef struct s_rdir
{
	int				type;
	int				here_doc_fd;
	char			*with;
	struct s_rdir	*next;
}	t_rdir;

typedef struct s_cmd
{
	char			*name;
	char			**content;
	struct s_rdir	*rdir;
	int				is_heredoc;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_parse
{
	char			*input;
	struct s_token	*chunks;
	struct s_token	*tokens;
}	t_parse;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_info
{
	struct s_env	*env_lst;
	int				last_exit_num;
}	t_info;

extern t_info	g_info;

void	parse(t_cmd **cmds);
char	**lst_to_arr(t_env *envs);
t_env	*new_env(char *key, char *value);
void	save_envs(char *envp[]);

void	define_signal(void);

#endif
