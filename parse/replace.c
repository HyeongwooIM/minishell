//
// Created by jiyun on 2023/01/19.
//
#include "minishell.h"
#include "./parse.h"

//t_env *find_env(char *key)
//{
//	t_env *temp;
//
//	temp = g_info.env_lst;
//	while (temp && ft_strcmp(temp->key, key))
//		temp = temp->next;
//	if (!temp)
//		return (0);
//	return (temp);
//}
//
//int count_value_size(char *str)
//{
//	t_env *env;
//	char *key;
//	int word_len;
//	int key_len;
//
//	word_len = 0;
//	key_len = 0;
//	if ('a' < *str && *str < 'z')
//		while (!is_space(*(str + key_len)))
//			key_len++;
//	else if ('0' < *str && *str < '9')
//		key_len++;
//	key = malloc(sizeof(char) * (key_len + 1));
//	if (!key)
//		exit (1);
//	ft_strlcpy(key, str, key_len);
//	env = find_env(key);
//	if (env)
//		word_len += ft_strlen(env->value);
//	free(key);
//	return (word_len);
//}
//
////$ 하나가 아니라 두개도 세개도 올 수 있으니까 문자열 다 돌면서 확인하기
////1. 바로 뒤에 문자가 오면 whitespace 전까지의 문자/문자열 모두를 가져가서 일치하는 환경변수가 있는지 찾음
////2. 바로 뒤에 숫자가 오면 그 숫자 하나만 가져가서 일치하는 환경변수가 있는지 찾음
////3. 바로 뒤에 ?가 오면 마지막 에러넘을 가져와서 $? 전체를 치환
////4. 바로 뒤에 _가 오면
////5. 바로 뒤에 whitespace나 공백이 오면 $포함하여 공백 전까지 출력
//
//void	substitute_dollar(char *str)
//{
//	char *start;
//	int word_len;
//
//	start = str + 1;
//	if ('a' < *start && *start < 'z' || \
//			'0' < *start && *start < '9')// $ 뒤에 문자나 숫자 있을 때
//		word_len += count_value_size(start);
//	else if (*start == '?') //?일 때
//		if (g_info.last_error)
//			word_len += ft_strlen(ft_itoa(g_info.last_error));
//			//last_error가 없으면(g_info 초기화시 NONE enum 필요할 듯) word_len에는 영향 x
//		else // !start || is_space(*start) || 그 외 기호들
//		{
//			str++;
//			continue;
//		}
//	str += word_len;
//}
//
//char	*join_pieces(char **pieces)
//{
//
//}
//
////환경변수 치환 시(1, 2) split이랑 join 필요
////split할 지점 찾기 -> split 하기 -> 환경변수 치환하기 -> join 하기
//
//

//void	free_all(char **ret)
//{
//	size_t	i;
//
//	i = 0;
//	while (ret[i] != 0)
//	{
//		free(ret[i]);
//		i++;
//	}
//	free(ret);
//}
//
//void    put_str(char **ret, char **start, char **end, int size, int i)
//{
//	int	j;
//
//	*end = *start + size;
//	ret[i] = malloc(sizeof(char) * (size + 1));
//	if (ret[i] == 0)
//	{
//		free_all(ret);
//		exit(1);
//	}
//	j = 0;
//	while (j < *end - *start)
//	{
//		ret[i][j] = (*start)[j];
//		(*start)++;
//		j++;
//	}
//	ret[i][j] = '\0';
//	*start = *end;
//}
//
//int count_pieces_num(char *str)
//{
//	int size;
//
//	size = 0;
//	while (*str)
//	{
//		if (*str == '$' && *(str + 1) && !is_space(*(str + 1)))
//		{
//			size++;
//			while (*(str + 1) && *(str + 1) != '$')
//			{
//				if (*(str + 1) == '\'' || is_space(*(str + 1)))
//				{
//					size++;
//					break ;
//				}
//				str++;
//			}
//		}
//		str++;
//	}
//	return (size);
//}
//
//
//char **malloc_pieces(char *word, int *size)
//{
//	char **ret;
//
//	*size = count_pieces_num(word);
//	ret = malloc(sizeof(char *) * (*(size + 1)));
//	if (!ret)
//		exit(1);
//	return (ret);
//}

char    *cut_substr(char *start, char *end)
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

char    **split_words(char *s, int *size)
{
    char **ret;
//	ret = malloc_pieces(s, size);
    char *start;
    char *tmp;

    ret = NULL;
    start = s;
    *size = 0;
//    chunk->word가 null일 수 있나?
//    if (!s)
//        exit (1);
    while (*s)
    {
        if (*s == '$')
        {
//            if (*(s + 1) && (s - start != 0) && is_space(*(s + 1))) // $ 포함 안된 문자열, 뒤에 공백
//			{
//				s++;
//				continue ;
//			}
			if (*(s + 1) == '?')
			{
				s++;
				tmp = cut_substr(start, ++s);
			}
			else if (*(s + 1) && (s - start != 0) && !is_space(*(s + 1))) // $ 포함 안된 문자열, 뒤에 공백 아닐
                tmp = cut_substr(start, s);
//			else if (*(s + 1) && (s - start == 0) && is_space(*(s + 1))) // $포함, 뒤에 공백
//			{
//				s++;
//				continue ;
//			}
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
            ret = ft_strjoin_1to2(ret, tmp);
            (*size)++;
            start = s;
            s--;
        }
        s++;
    }
    if (*size == 0 || s - start != 0)
    {
        ret = ft_strjoin_1to2(ret, start);
        *size = 1;
    }
    return (ret);
}

int main()
{
    char input[100] = "$?ere $  $"; //quote 잘 나누나?
//    char input[100] = "\"  \' \" a \'"; //quote 에러 잘 뱉나?
//    char input[50] = "<< END | > a";
    char **ret;
    int size;

    ret = split_words(input, &size);

    int i = 0;
    while (i < size)
    {
        printf("%s\n", ret[i]);
		i++;
    }
}

//char	*change_word(t_token *chunk)
//{
//	int i;
//	int cnt;
//	char **pieces;
//
//	pieces = split_words(chunk->word++, &cnt);
//
//	// 확인용
//	i = 0;
//	while (i < cnt)
//	{
//		printf("%s|\n", pieces[i]);
//		i++;
//	}
//
//
//	i = 0;
//	while (i < cnt)
//	{
//		if (pieces[i][0] == '$')
////            substitute_dollar(*pieces);
//			(*pieces)++;
//		i++;
//	}
////    return (join_pieces(pieces));
//	return (NULL);
//}
//
//
//void	replace_chunk(t_token *chunks)
//{
//	/* 치환 작업 및 제거
//	 * $와 "$" 뒤 문자와 일치하는 환경변수 key가 있으면 value로, 없으면 빈 문자열로 치환하면서
//	 	* $의 type은 DOLLAR -> CHAR "$"의 type은 D_QUOTE -> CHAR
//	 * ''는 ''만 제거
//	 	* ''의 type은 S_QUOTE -> CHAR
//	*/
//	t_token	*cur;
//	char *word;
//
//	cur = chunks;
//	while (cur != NULL)
//	{
//		if ((cur->type == DOLLAR) || \
//		(cur->type == D_QUOTE && ft_strchr(cur->word, '$')))
//			word = change_word(cur);
//		else if (cur->type == S_QUOTE)
//			word = ft_strdup(cur->word++);
//		else
//		{
//			cur = cur->next;
//			continue ;
//		}
//		cur->word = word;
//		cur->type = CHAR;
//		cur = cur->next;
//	}
//}
//
//int main()
//{
//    t_token	*chunks;
//
//    char input[100] = "\"  \'   \"  \'$HOME\' \"\'\""; //quote 잘 나누나?
////    char input[100] = "\"  \' \" a \'"; //quote 에러 잘 뱉나?
////    char input[50] = "<< END | > a";
//
//    chunks = init_token();
//    make_chunk_lst(input, chunks);
//
//    replace_chunk(chunks);
//}