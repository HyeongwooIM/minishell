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
		ft_error_exit("malloc error", 1);;
	i = -1;
	while (++i < dest_len)
		ret[i] = dest[i];
	i = -1;
	while (++i < src_len)
		ret[dest_len + i] = src[i];
	ret[dest_len + i] = '\0';
	free(dest);
	return (ret);
}

char	*env_value(char *str)
{
	t_env *env;
	char *ret;

	env = find_env(str);
	if (!env)
		return (0);
	ret = ft_strdup(env->value);
	return (ret);
}

char *get_word(char *key)
{
	char *ret;

	if (*key == '?')
	{
		ret = ft_itoa(g_info.last_exit_num);
		if (!ret)
			ft_error_exit("malloc error", 1);;
	}
	if (ft_isalpha(*key) || *key == '_')// $ 뒤에 문자나 숫자 있을 때, _있을 때
		ret = env_value(key);
	return (ret);
}

char	*join_pieces(char **strs)
{
	int i;
	int len;
	char *ret;

	i = -1;
	len = 0;
	if (!strs || !*strs)
		return (0);
	while (strs[++i])
		len += ft_strlen(strs[i]);
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		ft_error_exit("malloc error", 1);
	i = -1;
	while (strs[++i])
		ret = add_str(ret, strs[i]);
	return (ret);
}

char    *cut_substr(const char *start, const char *end)
{
    char *ret;
    int size;
    int i;

    size = end - start;
    ret = malloc(sizeof(char) * (size + 1));
    if (!ret)
        ft_error_exit("malloc error", 1);;
    i = 0;
    while(i < size)
    {
        ret[i] = start[i];
        i++;
    }
    ret[size] = '\0';
    return (ret);
}

char	**split_words(char *s)
{
    char **ret;
    char *start;
    char *tmp;
	int size;

    ret = NULL;
    start = s;
	size = 0;
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
            ret = ft_strjoin_1to2(ret, tmp);
			size++;
            start = s;
            s--;
        }
        s++;
    }
    if (size == 0 || s - start != 0)
    {
        ret = ft_strjoin_1to2(ret, start);
		size += 1;
    }
    return (ret);
}

char	*change_dollar(t_token *chunk)
{
	char *ret;

	ret = get_word(chunk->word + 1);
	if (!ret)
		return (0);
	return (ret);
}

char	*change_quote(t_token *chunk)
{
	char **after;
	char **before;
	char *tmp;
	char *ret;
	int i;

	after = NULL;
	before = split_words(dequote(chunk->word)); //" " 떼고 넣기
	i = -1;
	while (before[++i])
	{
		if (before[i][0] == '$')
		{
			tmp = get_word(&(before[i][1]));
			after = ft_strjoin_1to2(after, tmp);
			free(tmp);
		}
		else
			after = ft_strjoin_1to2(after, before[i]);
	}
	if (!after)
		return (0);
	ret = join_pieces(after);
	free_arr2(before);
	free_arr2(after);
    return (ret);
}

void	replace_chunk(t_parse *info)
{
	t_token	*cur;
	char *word;

	cur = info->chunks;
	while (cur != NULL)
	{
		if (cur->type == DOLLAR)
			word = change_dollar(cur);
		else if ((cur->type == D_QUOTE && ft_strchr(cur->word, '$')))
			word = change_quote(cur);
		else if (cur->type == S_QUOTE || \
		(cur->type == D_QUOTE && !ft_strchr(cur->word, '$')))
			word = dequote_h(cur->word, cur->type); //냅다 자르지 않기
		else
		{
			cur = cur->next;
			continue ;
		}
		if (!word)
			word = ft_strdup("");
		cur->word = word;
		cur->type = CHAR;
		cur = cur->next;
	}
}