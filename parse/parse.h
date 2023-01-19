//
// Created by jiyun on 2023/01/09.
//

#ifndef PARSE_H
#define PARSE_H

#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_chunk_type
{
	NONE = -42,
	CHAR,
	S_QUOTE, // ' '
	D_QUOTE, // " "
	DOLLAR, // $
	REDIRECT,
	PIPE
}	t_chunk_type;

typedef enum e_token_type
{
	CMD = -24,
	OPTION
}	t_token_type;

typedef struct s_token
{
	int type;
	char *word;
	struct s_token *next;
}	t_token;

/* utils.c */
int is_space(char c);
int	ft_strcmp(const char *str1, const char *str2);
t_token *init_token();
t_cmd	*init_cmd();
void	add_token_node(int type, char *word, t_token *head);
t_token	*new_token(int type, char *word);
t_rdir	*new_rdir(int type, char *with);
t_cmd	*init_cmd();
void	add_rdir_node(int type, char *with, t_rdir *rdir);

/* utils2.c */
char	**ft_strjoin1to2(char **dest, char *src);

/* chunks.c */
void	make_chunk_lst(char *input, t_token *chunks);

/* replace.c */
//void	replace_chunk(t_token *chunks);

/* tokens.c */
void    make_token_lst(t_token *chunks, t_token *tokens);

/* cmds.c */
void make_cmd_lst(t_token *tokens, t_cmd *cmds);

#endif
