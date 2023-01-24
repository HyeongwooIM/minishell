//
// Created by jiyun on 2023/01/19.
//
#include "includes/minishell.h"

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

    if (!*key)
    {
        free(key);
        return (strdup(""));
    }
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

//char	*join_pieces(char **strs)
//{
//	int i;
//	int len;
//	char *ret;
//
//	i = -1;
//	len = 0;
//	if (!strs || !*strs)
//		return (0);
//	while (strs[++i])
//		len += ft_strlen(strs[i]);
//	ret = malloc(sizeof(char) * (len + 1));
//	if (!ret)
//		ft_error_exit("malloc error", 1);
//	i = -1;
//	while (strs[++i])
//		ret = ft_strjoin_1to1(ret, strs[i]);
//	return (ret);
//}
//
//char    *cut_substr(const char *start, const char *end)
//{
//    char *ret;
//    int size;
//    int i;
//
//    size = end - start;
//    ret = malloc(sizeof(char) * (size + 1));
//    if (!ret)
//        ft_error_exit("malloc error", 1);;
//    i = 0;
//    while(i < size)
//    {
//        ret[i] = start[i];
//        i++;
//    }
//    ret[size] = '\0';
//    return (ret);
//}

char	**find_env_values(char *s, int *origin_len)
{
    char **ret;
    char *word;
    int d_quote_on;
    int s_quote_on;
    int num_on;
    int i;

    ret = NULL;
    d_quote_on = FALSE;
    s_quote_on = FALSE;
    num_on = FALSE;
    while (*s)
    {
        if (*s == '\"')
            d_quote_on = !d_quote_on;
        else if (*s == '\'')
            s_quote_on = !s_quote_on;
        else if (*s == '$')
        {
            if (d_quote_on == TRUE)
            {
                i = 0;
                while (s[++i] != '\0')
                {
                    if (ft_isdigit(s[i]))
                        num_on = !num_on;
                    if (s[i] == '\"' || s[i] == '$'|| is_space(s[i]) || \
                    (ft_isdigit(s[i]) && num_on == TRUE))
                        break ;
                }
                *origin_len = i - 1;
                word = get_word(ft_substr(s, 1, *origin_len)); //$ 뒤 문자만 갖다가 치환
                ret = ft_strjoin_1to2(ret, word); // word에도 ret에도 "" 들어갈 수 있음!
                free(word);
                s += *origin_len;
            }
        }
        s++;
    }
    return (ret);
}

char *change_word(t_token *cur)
{
	char **envs;
	char *ret;
	int origin_len;
	int i;

	envs = find_env_values(cur->word, &origin_len);
	i = -1;
	while (*cur->word)
	{
		if (*cur->word == '$')
		{
			if (envs)
				ret = ft_strjoin_1to1(ret, envs[++i]);
			cur->word += origin_len + 1;
		}
		else
		{
			ret  = ft_charjoin(ret, *cur->word);
			cur->word++;
		}
	}
	free_arr2(envs);
	return (ret);
}

void	replace_chunk(t_parse *info)
{
    t_token	*cur;
    char *word;

	cur = info->chunks;
	while (cur)
	{
        word = NULL;
		if (cur->type == CHAR)
		{
			if (strchr(cur->word, '$'))
			{
				word = change_word(cur);
				cur->word = ft_strdup(word);
				free(word);
			}
			if (strchr(cur->word, '\''))
				cur->word = dequote(cur->word, S_QUOTE);
			if (strchr(cur->word, '\"'))
				cur->word = dequote(cur->word, D_QUOTE);
		}
        cur = cur->next;
	}
}