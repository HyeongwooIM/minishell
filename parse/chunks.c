//
// Created by jiyun on 2023/01/17.
//
#include "minishell.h"
#include "parse.h"

int quote_size(const char *str, char quote)
{
	int i;
    int quote_close;

	i = 1;
    quote_close = 0;
	while (str[i])
	{
		if (str[i] == quote)
		{
			i++;
            quote_close = 1;
			break ;
		}
		i++;
	}
    if (quote_close == 0)
        exit(1);
	return (i);
}

int rdir_size(const char *str, char rdir)
{
	int i;

	i = 1;
	if (str[i] == rdir)
		i++;
	return (i);
}

int count_chunk_size(const char *str, char sign)
{
	int size;

	size = 0;
	if (sign == '\'' || sign == '\"')
		size = quote_size(str, sign);
	else if (sign == '>' || sign == '<')
		size = rdir_size(str, sign);
	return (size);
}

void	make_chunk(const char *chunk, int chunk_size, t_token *chunks)
{
	int		type;
	char	*word;
	int 	i;

	if (*chunk == '\'')
		type = S_QUOTE;
	else if (*chunk == '\"')
		type = D_QUOTE;
	else if (*chunk == '>' || *chunk == '<')
		type = REDIRECT;
	else if (*chunk == '|')
		type = PIPE;
	else if (*chunk == '$')
		type = DOLLAR;
	else
		type = CHAR;
	word = malloc(sizeof(char) * (chunk_size + 1));
	if (!word)
		return ;
	ft_strlcpy(word, chunk, chunk_size + 1);
	add_token_node(type, word, chunks);
}

void	make_chunk_lst(char *input, t_token *chunks)
{
	char *chunk_str;
	int chunk_size;

	while (*input)
	{
		while (is_space(*input))
			input++;
		chunk_str = input;
		chunk_size = 0;
		if (*input == '\'' || *input == '\"' || *input == '>' || *input == '<')
			chunk_size = count_chunk_size(input, *input);
		else
		{
			while (input[chunk_size])
			{
				if (is_space(input[chunk_size]))
					break ;
				chunk_size++;
			}
		}
		make_chunk(chunk_str, chunk_size, chunks);
		input = input + chunk_size;
	}
}