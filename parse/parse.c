//
// Created by jiyun on 2023/01/07.
//

// " ", ' ', $ 치환
// input token화
// token으로 실행부로 옮길 구조체 완성하기

#include "../minishell.h"
#include "./parse.h"

t_info g_info;

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

void	add_node(int type, char *word, t_token *head)
{
	if (head->word == NULL)
	{
		head->type = type;
		head->word = word;
	}
	else
	{
		while (head->next != NULL)
			head = head->next;
		head->next = new_token(type, word);
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
	else if (*chunk == '$')
		type = DOLLAR;
	else
		type = CHAR;
	word = malloc(sizeof(char) * (chunk_size + 1));
	if (!word)
		return ;
	i = -1;
	while (++i < chunk_size)
		word[i] = chunk[i];
	word[i] = '\0';
//	ft_strlcpy(word, chunk, chunk_size);
	add_node(type, word, chunks);
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

int	ft_strcmp(const char *str1, const char *str2)
{
	while (*str1 || *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

t_env *find_env(char *key)
{
	t_env *temp;

	temp = g_info.env_lst;
	while (temp && ft_strcmp(temp->key, key))
		temp = temp->next;
	if (!temp)
		return (0);
	return (temp);
}

/* $ 하나가 아니라 두개도 세개도 올 수 있으니까 문자열 다 돌면서 확인하기
 * 1. 바로 뒤에 문자가 오면 whitespace 전까지의 문자/문자열 모두를 가져가서 일치하는 환경변수가 있는지 찾음
 * 2. 바로 뒤에 숫자가 오면 그 숫자 하나만 가져가서 일치하는 환경변수가 있는지 찾음
 * 3. 바로 뒤에 ?가 오면 마지막 에러넘을 가져와서 $? 전체를 치환
 * 4. 바로 뒤에 whitespace나 공백이 오면 $포함하여 공백 전까지 출력
 */

/* 환경변수 치환 시(1, 2) split이랑 join 필요
 * split할 지점 찾기 -> split 하기 -> 환경변수 치환하기 -> join 하기
 */

char	*change_word(t_token *chunk)
{
	t_env *env;
	char *str;
	char *start;
	char *key;
	int	key_len;
	int word_len;

	str = chunk->word;
	key_len = 0;
	word_len = 0;
	while (*str)
	{
		while (*str == '$')
		{
			start = str + 1;
			if (!start || is_space(*start))
				break ;
			else if ('a' < *start && *start < 'z')// $ 뒤에 문자 있을 때
			{
				while (!is_space(*(start + key_len)))
					key_len++;
			}
			else if ('0' < *start && *start < '9') // $ 뒤에 숫자 있을 때
				word_len++;
		}
		word_len++;
		str++;


//		---------------------------------------------------------------
		if (*str == '?') //?일 때
		{
			if (g_info.last_error)
				word_len += ft_strlen(ft_itoa(g_info.last_error));
			//last_error가 없으면(g_info 초기화시 NONE enum 필요할 듯) word_len에는 영향 x
		}
		else // 일반 문자일 때
		{
			key_len = 1;
			while (!is_space(*(str + key_len)))
				key_len++;
			key = malloc(sizeof(char) * (key_len + 1));
			if (!key)
				exit (1);
			ft_strlcpy(key, str, key_len);
			env = find_env(key);
			free(key);
			if (env)
				word_len += ft_strlen(env->value);
			// env가 없으면 word_len에는 영향 x
		}
		str = str + word_len + 1;
	}
}

void	repair_chunk_lst(t_token *chunks)
{
	/* 치환 작업 및 제거
	 * $와 "$" 뒤 문자와 일치하는 환경변수 key가 있으면 value로, 없으면 빈 문자열로 치환하면서
	 	* $의 type은 DOLLAR -> CHAR "$"의 type은 D_QUOTE -> CHAR
	 * ''는 ''만 제거
	 	* ''의 type은 S_QUOTE -> CHAR
	*/
	t_token	*cur;
	char *word;

	cur = chunks;
	while (cur != NULL)
	{
		if (cur->type == DOLLAR)
			// $ 뒤 문자부터 공백까지의 단어를 뽑아서 일치하는 환경변수 key를 찾기
			word = change_word(cur); // $ 뒤부터
		else if (cur->type == D_QUOTE && \
		ft_strchr(cur->word, '$'))
				word = change_word(cur); // " 뒤부터
		else if (cur->type == S_QUOTE)
			word = cur->word++;
		else
		{
			cur = cur->next;
			continue ;
		}
		cur->word = word;
		cur->type = CHAR;
		cur = cur->next;
	}
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
	*/
	make_chunk_lst(input, chunks);

	/* "$" 치환 맟 '' 제거 */
	repair_chunk_lst(chunks);

	/* while
	 * token_lst 만들기
	 	* parse error 검사
	 	* lst 생성 및 추가
	 	* 청크 리스트를 토큰 리스트에 깊은 복사 하면서 cmd 인지 cmd에 딸린 옵션인지.. 확인하고 type 바꿔주기
	*/
//	make_token_lst(chunks, tokens);
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
	}

	/* 확인용 */
	while (tokens != NULL)
	{
		printf("%s\n", tokens->word);
		tokens = tokens->next;
	}
	printf("\n");
}

//테스트
