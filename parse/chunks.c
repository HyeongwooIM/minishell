//
// Created by jiyun on 2023/01/17.
//
#include "minishell.h"

int get_sign_size(const char *sign)
{
	int size;

	size = 1;
	if (*sign == '<')
	{
		if (*(sign + 1) == '<')
			size++;
	}
	if (*sign == '>')
	{
		if (*(sign + 1) == '>')
			size++;
	}
	return (size);
}

int get_chunk_size(char *str)
{
	int d_quote_on;
	int s_quote_on;
	int size;

	if (*str == '|' || *str == '<' || *str == '>')
		return (get_sign_size(str));
	d_quote_on = FALSE;
	s_quote_on = FALSE;
	size = 0;
	while (*str)
	{
		if (*str == '\'')
			s_quote_on = !s_quote_on;
		if (*str == '\"')
			d_quote_on = !d_quote_on;
		if (is_space(*str) || *str == '|' || \
		*str == '<' || *str == '>')
		{
			if (s_quote_on == FALSE && d_quote_on == FALSE)
				break ;
		}
		str++;
		size++;
	}
	return (size);
}

t_token	*make_raw_chunk_lst(char *input)
{
	t_token *lst;
	char *word;
	int size;

	lst = NULL;
	size = 0;
	while (is_space(*input))
		input++;
	while (*input)
	{
		size = get_chunk_size(input);
		word = ft_substr(input, 0,size);
		if (!word)
			ft_error_exit("malloc error\n", 1);
		add_token_node(NONE, word,&lst);
		input += size;
		while (is_space(*input))
			input++;
	}
	return (lst);
}

int get_chunk_type(char c)
{
	if (c == '<' || c == '>')
		return (REDIRECT);
	else if (c == '|')
		return (PIPE);
	else
		return (CHAR);
}

int	make_chunk_lst(t_parse *info)
{
	t_token *raw;
	t_token *tmp;
	char *word;
	int type;

	raw = make_raw_chunk_lst(info->input);
	tmp = raw;
	while (tmp)
	{
		type = get_chunk_type(*tmp->word);
		word = ft_strdup(tmp->word);
		add_token_node(type, word, &info->chunks);
		tmp = tmp->next;
	}
	free_token_lst(raw);
	return (0);
}