/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:24:45 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/08 17:49:12 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const	void *s, int c, size_t n)
{
	const unsigned char	*ptrs;

	ptrs = (const unsigned char *)s;
	while (n--)
	{
		if (*ptrs == (unsigned char)c)
			return ((void *)ptrs);
		ptrs++;
	}
	return (NULL);
}
