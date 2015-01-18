/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:46:05 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/10 18:18:19 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t		len_s2;

	len_s2 = ft_strlen(s2);
	if (!*s2)
		return ((char*)s1);
	while (*s1 && len_s2 <= n--)
	{
		if (!ft_memcmp(s1++, s2, len_s2))
			return ((char*)s1 - 1);
	}
	return (NULL);
}
