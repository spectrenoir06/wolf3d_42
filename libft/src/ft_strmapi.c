/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:53:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 12:57:11 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char			*str;
	unsigned int	i;
	size_t			l;

	if (s && f)
	{
		l = ft_strlen(s);
		str = (char *)malloc(sizeof(char) * (l + 1));
		if (!str)
			return (NULL);
		i = 0;
		while (i < l)
		{
			str[i] = (*f)(i, *s++);
			i++;
		}
		str[i] = 0;
		return (str);
	}
	return (NULL);
}
