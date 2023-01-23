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
        ft_error_exit("syntax error", 258);
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

void	make_chunk(const char *chunk, int chunk_size, t_parse *info)
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
		ft_error_exit("malloc error",1);
	ft_strlcpy(word, chunk, chunk_size + 1);
	add_token_node(type, word, &info->chunks);
}

int	make_chunk_lst(t_parse *info)
{
	char *input;
	int chunk_size;

	input = info->input;
	if (just_white_space(input))
		return (FAIL);
	while (*input)
	{
		while (is_space(*input))
			input++;
		if (!*input)
			break ;
		chunk_size = -1;
		if (*input == '\'' || *input == '\"' || *input == '>' || *input == '<')
			chunk_size = count_chunk_size(input, *input);
		else
			while (input[++chunk_size])
				if (is_space(input[chunk_size]))
					break ;
		make_chunk(input, chunk_size, info);
		input += chunk_size;
	}
	return (SUCCESS);
}