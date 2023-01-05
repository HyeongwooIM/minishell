/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyun <jiyun@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 18:10:06 by jiyun             #+#    #+#             */
/*   Updated: 2022/03/30 19:17:18 by jiyun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*cur;

	if (!lst || !f)
		return (0);
	new_lst = ft_lstnew((*f)(lst -> content));
	if (!new_lst)
		return (0);
	cur = new_lst;
	while (lst -> next != 0)
	{
		lst = lst -> next;
		cur -> next = ft_lstnew((*f)(lst -> content));
		if (!(cur -> next))
		{
			ft_lstclear(&new_lst, del);
			return (0);
		}
		cur = cur -> next;
	}
	return (new_lst);
}
