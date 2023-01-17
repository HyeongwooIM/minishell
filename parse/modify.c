//
// Created by jiyun on 2023/01/17.
//

#include "../minishell.h"
#include "parse.h"

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

int count_value_size(char *str)
{
	t_env *env;
	char *key;
	int word_len;
	int key_len;

	word_len = 0;
	key_len = 0;
	if ('a' < *str && *str < 'z')
		while (!is_space(*(str + key_len)))
			key_len++;
	else if ('0' < *str && *str < '9')
		key_len++;
	key = malloc(sizeof(char) * (key_len + 1));
	if (!key)
		exit (1);
	ft_strlcpy(key, str, key_len);
	env = find_env(key);
	if (env)
		word_len += ft_strlen(env->value);
	free(key);
	return (word_len);
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

void split_words(char *str, char **bowl)
{

}

void	substitute_dollar(char *str)
{
	char *start;
	int word_len;

	start = str + 1;
	if ('a' < *start && *start < 'z' || \
			'0' < *start && *start < '9')// $ 뒤에 문자나 숫자 있을 때
		word_len += count_value_size(start);
	else if (*start == '?') //?일 때
		if (g_info.last_error)
			word_len += ft_strlen(ft_itoa(g_info.last_error));
			//last_error가 없으면(g_info 초기화시 NONE enum 필요할 듯) word_len에는 영향 x
		else // !start || is_space(*start) || 그 외 기호들
		{
			str++;
			continue;
		}
	str += word_len;
}

char	*join_pieces(char **pieces)
{

}

int count_pieces_num(char *str)
{
	// 기준이 $만 있진 않지
	int	cnt;

	cnt = 1;
	while (*str)
	{
		if (*str == '$' && *(str + 1) && !is_space(*(str + 1)))
		{
			str++;
			cnt++;
			while (*(str + 1))
			{
				if (*(str + 1) == '\'' || is_space(*(str + 1)) || *(str + 1) == '$')
				{
					str++;
					cnt++;
					break ;
				}
				str++;
			}
		}
		str++;
	}
	return (cnt);
}

char	*change_word(t_token *chunk, int split_cnt)
{
	char **pieces;

	pieces = malloc(sizeof(char *) * (split_cnt + 1));
	if (!pieces)
		exit(1);
	split_words(chunk->word, pieces);
	while (*pieces)
	{
		if (*pieces[0] == '$')
			substitute_dollar(*pieces);
		(*pieces)++;
	}
	return (join_pieces(pieces));
}

void	modify_chunk_lst(t_token *chunks)
{
	/* 치환 작업 및 제거
	 * $와 "$" 뒤 문자와 일치하는 환경변수 key가 있으면 value로, 없으면 빈 문자열로 치환하면서
	 	* $의 type은 DOLLAR -> CHAR "$"의 type은 D_QUOTE -> CHAR
	 * ''는 ''만 제거
	 	* ''의 type은 S_QUOTE -> CHAR
	*/
	t_token	*cur;
	char *word;
	int cnt;

	cur = chunks;
	while (cur != NULL)
	{
		if ((cur->type == DOLLAR) || \
		(cur->type == D_QUOTE && ft_strchr(cur->word, '$')))
		{
			cnt = count_pieces_num(cur->word);
			word = change_word(cur, cnt);
		}
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

int main()
{
	int i;

	i = count_pieces_num("$   $HOME   ll   $");

	printf("%d\n", i);
}