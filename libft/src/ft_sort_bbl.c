/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_bbl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 17:37:25 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/02 17:37:27 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_sort_bbl(void **tab, int size, int (*f)(void *f1, void *f2))
{
	int		i;
	int		end;

	end = 0;
	while (!end)
	{
		end = 1;
		i = 0;
		while (i < (size - 1))
		{
			if (f(tab[i], tab[i + 1]))
			{
				ft_swap(&tab[i], &tab[i + 1]);
				end = 0;
			}
			i++;
		}
	}
}
