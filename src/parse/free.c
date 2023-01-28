#include "minishell.h"

void	free_token_lst(t_token *lst)
{
	t_token	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->word);
		free(lst);
		lst = tmp;
	}
}

void	free_rdir_lst(t_rdir *lst)
{
	t_rdir	*tmp;

	if (!lst)
		return ;
	while (lst)
	{
		tmp = lst->next;
		free(lst->with);
		free(lst);
		lst = tmp;
	}
}

void	free_arr2(char **ret)
{
	size_t	i;

	i = 0;
	if (!ret)
		return ;
	while (ret[i] != 0)
	{
		free(ret[i]);
		i++;
	}
	free(ret);
}
