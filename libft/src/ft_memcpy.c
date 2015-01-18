/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 07:08:00 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 07:55:37 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*ptrdst;
	const unsigned char	*ptrsrc;

	ptrdst = (unsigned char *)dst;
	ptrsrc = (const unsigned char *)src;
	while (n--)
		*ptrdst++ = *ptrsrc++;
	return (dst);
}
