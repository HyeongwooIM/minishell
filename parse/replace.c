#include "minishell.h"

char	*get_word(char *key)
{
	char	*ret;

	if (!key || !*key)
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

int	get_env_size(const char *s)
{
	int	i;

	i = 1;
	if (ft_isdigit(s[i]) || s[i] == '?')
		return (i + 1);
	while (s[i] != '\0')
	{
		if (!ft_isalnum_underbar(s[i]) || s[i] == '\"' || \
		s[i] == '$' || is_space(s[i]))
			break ;
		i++;
	}
	return (i);
}

int	replace_n_join(int env_size, char *word, char **s, char **tmp)
{
	char	*key;

	key = ft_substr((*s), 1, env_size - 1);
	if(!key)
		ft_error_exit("malloc error", 1);
	word = get_word(key);
	(*tmp) = ft_strjoin_1to1((*tmp), word);
	free(word);
	free(key);
	return (env_size - 1);
}

char	*change_word(char *s)
{
	char	*tmp;
	char	*word;
	int		d_quote_on;
	int		s_quote_on;

	tmp = NULL;
	d_quote_on = FALSE;
	s_quote_on = FALSE;
	while (*s)
	{
		if (*s == '\"' && s_quote_on == FALSE)
			d_quote_on = !d_quote_on;
		else if (*s == '\'' && d_quote_on == FALSE)
			s_quote_on = !s_quote_on;
		else if (*s == '$' && s_quote_on == FALSE && is_env(*(s + 1)))
			s += replace_n_join(get_env_size(s), word, &s, &tmp);
		else
		{
			word = ft_substr(s, 0, 1);
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
	char	*word;

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
}
