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
        return (0);
    }
	if (*key == '?')
	{
		ret = ft_itoa(g_info.last_exit_num);
		if (!ret)
			ft_error_exit("malloc error", 1);
	}
    else
        ret = env_value(key);
	return (ret);
}

char	*change_word(char *s)
{
	char *tmp;
	char *word;
	int d_quote_on;
	int s_quote_on;
    int num_on;
	int i;

	tmp = NULL;
	d_quote_on = FALSE;
	s_quote_on = FALSE;
    num_on = FALSE;
	while (*s)
	{
		if (*s == '\"' && s_quote_on == FALSE)
			d_quote_on = !d_quote_on;
		else if (*s == '\'' && d_quote_on == FALSE)
			s_quote_on = !s_quote_on;
		else if (*s == '$' && s_quote_on == FALSE && is_env(*(s + 1))) //is_env() 함수로 한번 더 거르고?
		{
			i = 1;
				while (s[i] != '\0')
				{
                    if (s[i] == '?')
                    {
                        i++;
                        break ;
                    }
                    if (ft_isdigit(s[i++]))
                        num_on = !num_on;
					if (!ft_isalnum_underbar(s[i]) || s[i] == '\"' || \
					s[i] == '$'|| is_space(s[i]) || (ft_isdigit(s[i]) && num_on == TRUE))
						break ;
					i++;
				}
				word = get_word(ft_substr(s, 1, i - 1)); //word는 null
				tmp = ft_strjoin_1to1(tmp, word);
				free(word);
				s += i - 1;
		}
		else
		{	word = ft_substr(s, 0, 1);
			tmp = ft_strjoin_1to1(tmp, word);
			free(word);
		}
		s++;
	}
	return (tmp);
}


void	replace_chunk(t_parse *info)
{
    t_token	*cur;
    char *word;

	cur = info->chunks;
	while (cur && cur->word && *cur->word)
	{
        word = NULL;
		if (cur->type == CHAR)
		{
			word = change_word(cur->word);
            if (word == NULL)
                cur->word = ft_strdup("");
            else
                cur->word = ft_strdup(word);
			free(word);
		}
        cur = cur->next;
	}
	debug_print_replced_chunks(info->chunks, 0);
}

void debug_print_replced_chunks(t_token *chunks, int i) {
	if (chunks == NULL)
		return ;
	printf("   REPLACED chunks %d: type=%d word=%s\n", i, chunks->type, chunks->word);
	debug_print_replced_chunks(chunks->next, ++i);
}