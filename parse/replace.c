//
// Created by jiyun on 2023/01/19.
//
#include "minishell.h"

void debug_print_replced_chunks(t_token *chunks, int i);

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

char	*change_word(char *s, int *origin_len)
{
	char *tmp = ft_strdup("");
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
		if (*s == '\"' && s_quote_on == FALSE)
			d_quote_on = !d_quote_on;
		else if (*s == '\'' && d_quote_on == FALSE)
			s_quote_on = !s_quote_on;
		else if (*s == '$' && s_quote_on == FALSE)
		{
			i = 1;
				while (s[i] != '\0')
				{
					if (ft_isdigit(s[i]))
						num_on = !num_on;
					if (!isalpha(s[i]) || s[i] == '\"' || s[i] == '$'|| is_space(s[i]) || \
                    (ft_isdigit(s[i]) && num_on == TRUE))
						break ;
					i++;
				}
				*origin_len = i - 1;
				word = get_word(ft_substr(s, 1, *origin_len)); //$ 뒤 문자만 갖다가 치환
				tmp = ft_strjoin_1to1(tmp, word);
				ret = ft_strjoin_1to2(ret, word); // word에도 ret에도 "" 들어갈 수 있음!
				free(word);
				s += *origin_len;
		}
		else
		{
			tmp = ft_strjoin_1to1(tmp, ft_substr(s, 0, 1));
		}
		s++;
	}
	printf("here~~~~~~~~~~~~ %s\n", tmp);
	return (tmp);
}

//char *change_word(t_token *cur)
//{
//	char **envs;
//	char *ret;
//	int origin_len;
//	int i;
//
//	envs = find_env_values(cur->word, &origin_len);
//	i = -1;
//	while (*cur->word)
//	{
//		if (*cur->word == '$')
//		{
//			if (envs)
//				ret = ft_strjoin_1to1(ret, envs[++i]);
//			cur->word += origin_len + 1;
//		}
//		else
//		{
//			ret  = ft_charjoin(ret, *cur->word);
//			cur->word++;
//		}
//	}
//	free_arr2(envs);
//	return (ret);
//}


void	replace_chunk(t_parse *info)
{
    t_token	*cur;
    char *word;
	int origin_len;

	cur = info->chunks;
	while (cur && cur->word && *cur->word)
	{
        word = NULL;
		if (cur->type == CHAR)
		{

				word = change_word(cur->word, &origin_len);
				cur->word = ft_strdup(word);
				free(word);
//			if (strchr(cur->word, '\'') || strchr(cur->word, '\"'))
//				cur->word = dequote(cur->word);
		}
        cur = cur->next;
	}
	debug_print_replced_chunks(info->chunks, 0);
}

//void	replace_chunk(t_parse *info)
//{
//	t_token	*cur;
//	char *word;
//	int d_q;
//	int s_q;
//
//	d_q = 0;
//	s_q = 0;
//	cur = info->chunks;
//	word = cur->word;
//	if(cur->type == CHAR)
//	{
//		while (cur && word && *word)
//		{
//			if (*word == '\"' && s_q == 0 )
//				d_q = 1;
//			else if (*word == '\'' && d_q == 0 )
//				s_q = 1;
//			if (*word)
//
//
//		}
//	}
//	debug_print_replced_chunks(info->chunks, 0);
//}

void debug_print_replced_chunks(t_token *chunks, int i) {
	if (chunks == NULL)
		return ;
	printf("   REPLACED chunks %d: type=%d word=%s\n", i, chunks->type, chunks->word);
	debug_print_replced_chunks(chunks->next, ++i);
}