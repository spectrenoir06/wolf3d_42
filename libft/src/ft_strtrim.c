/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 18:35:32 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/10 18:24:38 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_sp(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

char				*ft_strtrim(const char *s)
{
	char			*dst;
	size_t			i;
	size_t			e;

	if (!s)
		return (NULL);
	i = 0;
	while (ft_sp(*s++))
		i++;
	s -= i + 1;
	e = ft_strlen(s) - 1;
	if (!*s || e == i - 1)
		return (dst = ft_strnew(1));
	if (i != (e + 1))
		while (ft_sp(s[e]))
			e--;
	dst = ft_strsub(s, i, (e - i + 1));
	return (dst);
}
