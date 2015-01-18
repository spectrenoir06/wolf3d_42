/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 19:03:44 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/05 15:45:05 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*s;

	s = s1;
	while (*s)
		s++;
	while (n)
	{
		if (n < 1)
			*s = 0;
		else
			*s = *s2;
		n--;
		s++;
		s2++;
	}
	*s = 0;
	return (s1);
}
