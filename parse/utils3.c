#include "minishell.h"

int is_env(char c)
{
    if (c == '\0')
        return (0);
    if (c == '\"')
        return (0);
    if (is_space(c))
        return (0);
    if (c == '$')
        return (0);
    return (1);
}

int	ft_isalnum_underbar(int c)
{
	if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '_')
		return (1);
    if (('0' <= c && c <= '9'))
        return (1);
	return (0);
}