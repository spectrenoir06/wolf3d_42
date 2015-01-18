/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 19:27:59 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/11 15:08:07 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*new_list;
	t_list		*start;
	t_list		*tmp;

	if (!lst || !f)
		return (NULL);
	tmp = (*f)(lst);
	new_list = ft_lstnew(tmp->content, tmp->content_size);
	if (!new_list)
		return (NULL);
	start = new_list;
	while (lst->next)
	{
		tmp = f(lst->next);
		ft_lstadd(&new_list->next, ft_lstnew(tmp->content, tmp->content_size));
		if (!new_list)
			return (NULL);
		lst = lst->next;
		new_list = new_list->next;
	}
	return (start);
}
