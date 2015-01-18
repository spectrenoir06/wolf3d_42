/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 07:41:29 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/10 14:31:23 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*ptrdst;
	const unsigned char	*ptrsrc;
	unsigned char		cara;

	if (!src || !dst)
		return (NULL);
	ptrdst = (unsigned char *)dst;
	ptrsrc = (const unsigned char *)src;
	cara = (unsigned char)c;
	while (n--)
		if ((*ptrdst++ = *ptrsrc++) == cara)
			return (ptrdst);
	return (NULL);
}
