//
// Created by jiyun on 2023/01/09.
//

#ifndef PARSE_H
#define PARSE_H

#include "minishell.h"

typedef struct s_token t_token;
typedef struct s_rdir t_rdir;
typedef struct s_cmd t_cmd;

#define NO_ENV_VALUE -1

/* utils.c */
int is_space(char c);
int	ft_strcmp(const char *str1, const char *str2);
t_token *init_token();
t_cmd	*init_cmd();
void	add_token_node(int type, char *word, t_token *head);
t_token	*new_token(int type, char *word);
void	delete_token(t_token *token, int idx);
t_rdir	*new_rdir(int type, char *with);
t_cmd	*init_cmd();
void	add_rdir_node(int type, char *with, t_rdir *rdir);

/* utils2.c */
void	free_token_lst(t_token *lst);
void	free_arr2(char **ret);
char	**ft_strjoin_1to2(char **dest, char *src);

/* chunks.c */
void	make_chunk_lst(char *input, t_token *chunks);

/* replace.c */
void	replace_chunk(t_token *chunks);

/* tokens.c */
void    make_token_lst(t_token *chunks, t_token *tokens);

/* cmds.c */
void make_cmd_lst(t_token *tokens, t_cmd *cmds);

#endif
