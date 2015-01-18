/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 16:04:46 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/04 16:14:46 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	l;
	size_t	i;

	i = 0;
	l = ft_strlen(src);
	while (n > 0)
	{
		if (i > l)
			dst[i] = 0;
		else
			dst[i] = src[i];
		i++;
		n--;
	}
	return (dst);
}
