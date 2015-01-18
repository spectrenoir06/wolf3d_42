/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 14:37:28 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/08 14:33:01 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strnew(size_t size)
{
	char *ptr;

	ptr = (char *)malloc(size);
	if (!ptr)
		return (NULL);
	while (size--)
		ptr[size + 1] = 0;
	*ptr = 0;
	return (ptr);
}
