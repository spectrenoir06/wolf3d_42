/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 16:12:16 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/08 17:39:43 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(const void *content, size_t content_size)
{
	t_list		*t;

	t = (t_list *)malloc(sizeof(t_list));
	if (!t)
		return (NULL);
	if (!content)
	{
		t->content_size = 0;
		t->content = NULL;
	}
	else
	{
		t->content = (void *)malloc(content_size);
		if (!t->content)
			return (NULL);
		t->content_size = content_size;
		ft_memcpy(t->content, content, content_size);
	}
	t->next = NULL;
	return (t);
}
