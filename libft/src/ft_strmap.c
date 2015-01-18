/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 16:53:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/08 15:11:39 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(const char *s, char (*f)(char))
{
	char *str;
	char *ret;

	if (s && f)
	{
		str = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
		if (!str)
			return (NULL);
		ret = str;
		while (*s)
		{
			*str = (*f)(*s);
			str++;
			s++;
		}
		*str = 0;
		return (ret);
	}
	return (NULL);
}
