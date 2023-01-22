//
// Created by jiyun on 2023/01/19.
//
#include "minishell.h"
#include "parse.h"

char	*add_str(char *dest, char *src)
{
	char *ret;
	int dest_len;
	int src_len;
	int i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	ret = malloc(sizeof(char) * (dest_len + src_len + 1));
	if (!ret)
		exit(1);
	i = -1;
	while (++i < dest_len)
		ret[i] = dest[i];
	i = -1;
	while (++i < src_len)
		ret[dest_len + i] = src[i];
	ret[dest_len + i] = '\0';
	return (ret);
}

char	*env_value(char *str)
{
	t_env *env;
	char *key;
	char *ret;
	int key_len;

//	key_len = 0;
//	while (!is_space(*(str + key_len)))
//			key_len++;
//	key = malloc(sizeof(char) * (key_len + 1));
//	if (!key)
//		exit (1);
//	ft_strlcpy(key, str, key_len);
	env = find_env(str);
//	free(key);
	if (!env)
		return (0);
	ret = ft_strdup(env->value);
	if (!ret)
		exit (1);
	return (ret);
}

//$ 하나가 아니라 두개도 세개도 올 수 있으니까 문자열 다 돌면서 확인하기
//1. 바로 뒤에 문자가 오면 whitespace 전까지의 문자/문자열 모두를 가져가서 일치하는 환경변수가 있는지 찾음
//2. 바로 뒤에 숫자가 오면 그 숫자 하나만 가져가서 일치하는 환경변수가 있는지 찾음
//3. 바로 뒤에 ?가 오면 마지막 에러넘을 가져와서 $? 전체를 치환
//4. 바로 뒤에 _가 오면
//5. 바로 뒤에 whitespace나 공백이 오면 $포함하여 공백 전까지 출력

char *replace_dollar(t_token *pieces)
{
	char *start;
	char *tmp;
	char *ret;

	start = pieces->word + 1;
	if (ft_isalpha(*start) || *start != '_')// $ 뒤에 문자나 숫자 있을 때, _있을 때
		tmp = env_value(start);
	if (*start == '?')
	{
		tmp = ft_itoa(g_info.last_error);
		if (!tmp)
			exit (1);
	}
	return (tmp);
}

char	*join_pieces(t_token *pieces)
{
	t_token *tmp;
	char *ret;
	int	len;
	int i;

	tmp = pieces;
	len = 0;
	while (tmp)
	{
		len += ft_strlen(tmp->word);
		tmp = tmp->next;
	}
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		exit(1);
	i = -1;
	tmp = pieces;
	while (tmp)
	{
		ret = add_str(ret, tmp->word);
		tmp = tmp->next;
	}
	return (ret);
}

//환경변수 치환 시(1, 2) split이랑 join 필요
//split할 지점 찾기 -> split 하기 -> 환경변수 치환하기 -> join 하기

char    *cut_substr(const char *start, const char *end)
{
    char *ret;
    int size;
    int i;

    size = end - start;
    ret = malloc(sizeof(char) * (size + 1));
    if (!ret)
        exit(1);
    i = 0;
    while(i < size)
    {
        ret[i] = start[i];
        i++;
    }
    ret[size] = '\0';
    return (ret);
}

t_token	*split_words(char *s, int *size)
{
//    char **ret;
    char *start;
    char *tmp;
	t_token *ret;

	ret = init_token();
//    ret = NULL;
    start = s;
    *size = 0;
//    chunk->word가 null일 수 있나?
//    if (!s)
//        exit (1);
    while (*s)
    {
        if (*s == '$')
        {
//			$ 포함 안된 문자열, 뒤에 공백
			if (*(s + 1) == '?')
			{
				s++;
				tmp = cut_substr(start, ++s);
			}
			else if (*(s + 1) && (s - start != 0) && !is_space(*(s + 1))) // $ 포함 안된 문자열, 뒤에 공백 아닐
                tmp = cut_substr(start, s);
//			$ 포함, 뒤에 공백
			else if (*(s + 1) && (s - start == 0) && !is_space(*(s + 1))) // $포함, 뒤에 문자(a-z, _, ?)
            {
				if (!ft_isalpha(*(s + 1)) && *(s + 1) != '_')
				{
					s++;
					continue ;
				}
                while (*(s + 1) && *(s + 1) != '$' && *(s + 1) != '\'' && !is_space(*(s + 1)))
                    s++;
                tmp = cut_substr(start, ++s);
            }
			else
			{
				s++;
				continue;
			}
//            ret = ft_strjoin_1to2(ret, tmp);
			add_token_node(CHAR, tmp, ret);
            (*size)++;
            start = s;
            s--;
        }
        s++;
    }
    if (*size == 0 || s - start != 0)
    {
//        ret = ft_strjoin_1to2(ret, start);
		add_token_node(CHAR, ft_strdup(start), ret);
        *size += 1;
    }
    return (ret);
}

char	*change_word(t_token *chunk)
{
	int i;
	int cnt;
	char *ret;
	t_token *pieces;
	t_token *tmp;

	chunk->word[ft_strlen(chunk->word) - 1] = '\0';
	pieces = split_words(++chunk->word, &cnt); //" " 떼고 넣기
	tmp = pieces;
	i = 0;
	while (tmp)
	{
		if (*(tmp->word) == '$')
		{
			tmp->word = replace_dollar(tmp);
			if (!tmp->word) //env가 없어서 치환할게 없을 때
				delete_token(pieces, i);
		}
		tmp = tmp->next;
		i++;
	}
	ret = join_pieces(pieces);
	free_token_lst(pieces);
    return (ret);
}


void	replace_chunk(t_token *chunks)
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
		if ((cur->type == DOLLAR) || \
		(cur->type == D_QUOTE && ft_strchr(cur->word, '$')))
			word = change_word(cur);
		else if (cur->type == S_QUOTE || \
		(cur->type == D_QUOTE && !ft_strchr(cur->word, '$')))
		{
			cur->word[ft_strlen(cur->word) - 1] = '\0';
			word = ft_strdup(++cur->word);
		}
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

//int main()
//{
//    t_token	*chunks;
//
//    char input[100] = "\"  '$HOME'  $ \""; //quote 잘 나누나?
////    char input[100] = "\"  \' \" a \'"; //quote 에러 잘 뱉나?
////    char input[50] = "<< END | > a";
//
//    chunks = init_token();
//    make_chunk_lst(input, chunks);
//
//    replace_chunk(chunks);
//}