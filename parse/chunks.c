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
        return (-1); // TODO 고쳐야함
	while (!is_space(str[i]) && str[i] != '|' && str[i] != '>' && str[i] != '<' && str[i] != '\0')
		i++;
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

int count_size_1(char *str)
{
	int size;

	size = 0;
	if (*str == '>' || *str == '<')
		size = rdir_size(str, *str);
	if (*str == '|')
		size = 1;
	return (size);
}

int	count_size_2(char *str)
{

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
	int size;

	input = info->input;
	while (*input)
	{
		while (is_space(*input))
			input++;
		if (!*input)
			break ;
		if ( *input == '<' || *input == '>' || *input == '|')
			size = count_small_size(input);
		else if (*input == '\'' || *input == '\"')
			size = count_size_2(input);
			while (*input)
			{
				if (*input == '\'' || *input == '\"')
					check_unquoted();
				if (is_space(*input) || *input == '<' || *input == '>' || *input == '|')

			}
	}
	return (0);
}