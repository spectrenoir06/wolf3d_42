/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 14:50:44 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/07 17:07:41 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		count(int i)
{
	int			j;

	j = 0;
	while (i /= 10)
		j++;
	return (j + 1);
}

char			*ft_itoa(int i)
{
	size_t		size;
	char		*ret;
	char		*str;

	size = count(i);
	ret = (char *)malloc(sizeof(char) * (size + (i < 0 ? 1 : 0) + 1));
	if (!ret)
		return (NULL);
	str = ret;
	if (i == -2147483648)
		return (ft_strcpy(str, "-2147483648"));
	if (i < 0)
	{
		*str++ = '-';
		i = -i;
	}
	str += size - 1;
	*(str + 1) = 0;
	while (size--)
	{
		*str-- = (char)(i % 10 + '0');
		i /= 10;
	}
	return (ret);
}
