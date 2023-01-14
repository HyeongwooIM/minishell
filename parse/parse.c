//
// Created by jiyun on 2023/01/07.
//

// " ", ' ', $ 치환
// input token화
// token으로 실행부로 옮길 구조체 완성하기

#include "minishell.h"
#include "./parse.h"

int is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || \
			c == '\n' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

void	add_token(t_token **tokens, const char *chunk, int chunk_size)
{
	int		type;
	char	*word;
	int 	i;
	t_token *tmp;

	if (*chunk == '\'')
		type = S_QUOTE;
	else if (*chunk == '\"')
		type = D_QUOTE;
	else if (*chunk == '>' || *chunk == '<')
		type = REDIRECT;
	else if (*chunk == '|')
		type = PIPE;
	else
		type = STR;
	word = malloc(sizeof(char) * (chunk_size + 1));
	if (!word)
		return ;
	i = -1;
	while (++i < chunk_size)
		word[i] = chunk[i];
	word[i] = '\0';
	tmp = malloc(sizeof(t_token) * 1);
	tmp->word = word;
	tmp->type = type;
	if (*tokens == NULL)
		*tokens = tmp;
	else
	{
		while (*tokens != NULL)
			*tokens = (*tokens)->next;
		(*tokens)->next = tmp;
	}
}

void	input_tokenize(char *input, t_token **tokens)
{
	char *chunk;
	int chunk_size;

	tokens = malloc(sizeof(t_token) * 1);
	if (!tokens)
		return ;
	while (*input != '\0' || *input != '\n')
	{
		while (is_space(*input))
			input++;
		chunk = input;
		chunk_size = 1;
		if (*input == '\'')
		{
			while (input[chunk_size] != '\'')
			{
				if (input[chunk_size] == '\0')
					// 안 닫혔을 때: syntax error?
					return ;
				chunk_size++;
			}
		}
		else if (*input == '\"')
		{
			while (input[chunk_size] != '\"')
			{
				if (input[chunk_size] == '\0')
					// 안 닫혔을 때: syntax error?
					return ;
				chunk_size++;
				printf("%c", input[chunk_size]);
			}
		}
		else if (*input == '>')
		{
			if (input[chunk_size] != '>')
				chunk_size++;
		}
		else if (*input == '<')
		{
			if (input[chunk_size] != '<')
				chunk_size++;
		}
		else
		{
			while (is_space(*input) || input[chunk_size] == '\0')
				chunk_size++;
		}
		add_token(tokens, chunk, chunk_size);
		input = input + chunk_size;
	}
}

int	parse(void)
{
	char *input;
	t_token *tokens;

//	while (1)
	{
		input = readline("minishell$ ");
		// token화 하기
		input_tokenize(input, &tokens);
	}
	/* 토큰 확인 */
	while (tokens != NULL)
	{
		printf("%s\n", tokens->word);
		tokens = tokens->next;
	}
	printf("\n");
}

//테스트
