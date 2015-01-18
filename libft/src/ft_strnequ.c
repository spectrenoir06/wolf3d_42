/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:28:17 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/09 13:00:49 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(const char *s1, const char *s2, size_t i)
{
	if (!s1 || !s2)
		return (0);
	while (i--)
		if (*s1++ != *s2++)
			return (0);
	return (1);
}
