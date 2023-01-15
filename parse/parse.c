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

void	add_token(int type, char *word, t_token **tokens)
{
	if ((*tokens)->word == NULL)
	{
		(*tokens)->type = type;
		(*tokens)->word = word;
	}
	else
	{
		while ((*tokens)->next != NULL)
			*tokens = (*tokens)->next;
		(*tokens)->next = new_token(type, word);
	}
}

void	make_token(const char *chunk, int chunk_size, t_token **tokens)
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
	add_token(type, word, tokens);
}

int quote_size(char *str, char quote)
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

int rdir_size(char *str, char rdir)
{
	int i;

	i = 1;
	if (str[i] == rdir)
		i++;
	return (i);
}

/* 추후 함수명 make_chunk로 변경 */
void	input_tokenize(char *input, t_token **tokens)
{
	t_token	*head;
	char *chunk;
	int chunk_size;

	*tokens = new_token(0, NULL);
//	NULL 가드
	head = *tokens;
	while (*input)
	{
		while (is_space(*input))
			input++;
		chunk = input;
		chunk_size = 1;
		if (*input == '\'')
			chunk_size = quote_size(input, '\'');
		else if (*input == '\"')
			chunk_size = quote_size(input, '\"');
		else if (*input == '>')
			chunk_size = rdir_size(input, '>');
		else if (*input == '<')
			chunk_size = rdir_size(input, '<');
		else
		{
			while (input[chunk_size])
			{
				if (is_space(input[chunk_size]))
					break ;
				chunk_size++;
			}
		}
		make_token(chunk, chunk_size, &head);
		input = input + chunk_size;
	}
}

/* input_tokenize 개괄 */
//void	input_tokenize(char *input, t_token **tokens)
//{
//	/* token 할당 */
//	/* while
//	 * chunk_lst 만들기
//	 	* size 재기(일단 white space 기준으로)
//	 	* lst 생성 혹은 추가
//	*/
//	chunks = make_chunk(input, tokens);
//	/* while
//	 * token_lst 만들기
//	 	* parse error 검사
//	 	* "$" 치환 맟 "" 제거
//	 	* lst 생성 및 추가
//	*/
//	tokens = make_token();
//}

int	main(void)
{
	char *input;
	t_token *tokens;

//	while ()
	{
		input = readline("minishell$ ");
		// token화 하기
		input_tokenize(input, &tokens); // error를 받아서 여기서 free하기
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
