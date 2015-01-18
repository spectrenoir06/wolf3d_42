/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 17:14:49 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/09 13:24:09 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*r;

	r = NULL;
	while (*s)
	{
		if (*s == c)
			r = (char *)s;
		s++;
	}
	if (!r && c)
		return (0);
	return (!c ? (char *)s : r);
}
