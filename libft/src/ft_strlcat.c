/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/05 16:03:23 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 17:23:18 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	buff;
	size_t	len2;
	size_t	n_ori;

	i = 0;
	n_ori = size;
	len2 = ft_strlen(src);
	buff = ft_strlen(dest) + len2;
	while (*dest && size)
	{
		size--;
		dest++;
	}
	if (size == 0)
		return (n_ori + len2);
	while (src[i] && size-- > 1)
		*dest++ = src[i++];
	*dest = 0;
	return (buff);
}
