/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 08:34:36 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 14:33:27 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char		*ptrs1;
	const unsigned char		*ptrs2;

	ptrs1 = s1;
	ptrs2 = s2;
	while (n--)
	{
		if (*ptrs1 != *ptrs2)
			return (*ptrs1 - *ptrs2);
		ptrs1++;
		ptrs2++;
	}
	return (0);
}
