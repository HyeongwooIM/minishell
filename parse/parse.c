//
// Created by jiyun on 2023/01/07.
//

// " ", ' ', $ 치환
// input token화
// token으로 실행부로 옮길 구조체 완성하기

#include "../minishell.h"
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
		exit(1);
	node->type = type;
	node->word = word;
	node->next = NULL;
	return (node);
}

int quote_size(const char *str, char quote)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == '\0')
			// 안 닫혔을 때: syntax error?
			exit(1);
		if (str[i] == quote)
		{
			i++;
			break ;
		}
		i++;
	}
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

int count_size(const char *str, char sign)
{
	int size;

	size = 0;
	if (sign == '\'' || sign == '\"')
		size = quote_size(str, sign);
	else if (sign == '>' || sign == '<')
		size = rdir_size(str, sign);
	return (size);
}

void	add_chunk(int type, char *word, t_token *chunk)
{
	if (chunk->word == NULL)
	{
		chunk->type = type;
		chunk->word = word;
	}
	else
	{
		while (chunk->next != NULL)
			chunk = chunk->next;
		chunk->next = new_token(type, word);
	}
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
	else
		type = STR;
	word = malloc(sizeof(char) * (chunk_size + 1));
	if (!word)
		return ;
	i = -1;
	while (++i < chunk_size)
		word[i] = chunk[i];
	word[i] = '\0';
	add_chunk(type, word, chunks);
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
			chunk_size = count_size(input, *input);
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

void	make_token_lst(t_token *chunks, t_token *tokens)
{
	// 치환 작업
	// 제거 작업
}

void	input_tokenize(char *input, t_token *tokens)
{
	t_token	*chunks;

	/* token 할당 */

	chunks = new_token(0, NULL);
	//null 가드
	/* while
	 * chunk_lst 만들기
	 	* size 재기(일단 white space 기준으로)
	 	* lst 생성 혹은 추가
	*/
	make_chunk_lst(input, chunks);
	/* while
	 * token_lst 만들기
	 	* parse error 검사
	 	* "$" 치환 맟 "" 제거
	 	* lst 생성 및 추가
	*/
	make_token_lst(chunks, tokens);
}

int	main(void)
{
	char *input;
	t_token *tokens;

//	while ()
	{
		input = readline("minishell$ ");
		tokens = new_token(0, NULL);
		// token화 하기
		input_tokenize(input, tokens); // error를 받아서 여기서 free하기
		//$ 치환

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
