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

t_token	*new_token(int type, char *word)
{
	t_token *node;

	node = malloc(sizeof(t_token) * 1);
	if (!node)
		return (NULL);
	node->type = type;
	node->word = word;
	node->next = NULL;
	return (node);
}

void	add_token(t_token **tokens, int type, char *word)
{
	if (*tokens == NULL)
		*tokens = new_token(type, word);
	else
	{
		while ((*tokens)->next != NULL)
			*tokens = (*tokens)->next;
		(*tokens)->next = new_token(type, word);
	}
}

void	make_token(t_token **tokens, const char *chunk, int chunk_size)
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
	add_token(tokens, type, word);
}

void	input_tokenize(char *input, t_token **tokens)
{
	char *chunk;
	int chunk_size;

	tokens = malloc(sizeof(t_token *) * 1);
	// NULL가드
	while (*input)
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
					exit(1);
				chunk_size++;
			}
		}
		else if (*input == '\"')
		{
			while (input[chunk_size] != '\"')
			{
				if (input[chunk_size] == '\0')
					// 안 닫혔을 때: syntax error?
					exit(1);
				chunk_size++;
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
		chunk_size++;
		make_token(tokens, chunk, chunk_size);
		input = input + chunk_size;
	}
}

int	main(void)
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
