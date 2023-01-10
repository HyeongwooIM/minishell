//
// Created by jiyun on 2023/01/09.
//

#ifndef PARSE_H
#define PARSE_H

#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_token_type
{
	STR,
	CMD,
	OPTION,
	S_QUOTE, // ' '
	D_QUOTE, // " "
	REDIRECT,
	PIPE
}	t_token_type;

typedef struct s_token
{
	int type;
	char *word;
	struct s_token *next;
}	t_token;


#endif
