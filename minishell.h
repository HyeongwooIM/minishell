//
// Created by jiyun on 2023/01/05.
//

#ifndef MINISHELL_H
#define MINISHELL_H

#include "libft/libft.h"
#include <stdio.h>

typedef enum e_rdir_type
{
	RDIR, // >
	R_RDIR, // <
	D_RDIR, // >>
	HEREDOC // <<
}	t_rdir_type;

typedef struct s_rdir
{
	int type;
	char *with; //filename or endpoint(heredoc)
	struct s_rdir *next;
}	t_rdir;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}	t_env;

extern t_env g_env;

typedef struct s_cmd
{
	// input: cat (null) > a > b < c < d (no option)
	char *name; // ex : "cat"
	char **content; // ex : NULL
	struct t_rdir *rdir; // rdir->type: RDIR(>), rdir->file: "a", rdir->next->type: RDIR(>), rdir->next->file: "b" ...
	int is_heredoc; // heredoc 여부
	struct s_cmd *next;
}	t_cmd;

#endif
