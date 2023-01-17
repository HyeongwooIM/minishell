//
// Created by jiyun on 2023/01/09.
//

#ifndef PARSE_H
#define PARSE_H

#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_chunk_type
{
	CHAR,
	S_QUOTE, // ' '
	D_QUOTE, // " "
	DOLLAR, // $
	REDIRECT,
	PIPE
}	t_chunk_type;

typedef enum e_token_type
{
	CMD,
	OPTION,
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
t_token	*new_token(int type, char *word);
void	add_node(int type, char *word, t_token *head);

/* chunk.c */
void	make_chunk_lst(char *input, t_token *chunks);

/* repair.c */
void	modify_chunk_lst(t_token *chunks);

#endif
