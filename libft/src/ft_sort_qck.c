/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_qck.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/02 17:37:13 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/02 17:37:17 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		sort(void **tab, int bg, int ed, int (*f)(void *, void *))
{
	void		*pvt;
	int			lft;
	int			rgt;

	pvt = tab[bg];
	lft = bg - 1;
	rgt = ed + 1;
	if (bg >= ed)
		return ;
	while (1)
	{
		while (f(tab[--rgt], pvt) > 0)
			;
		while (f(tab[++lft], pvt) < 0)
			;
		if (lft < rgt)
			ft_swap(&tab[lft], &tab[rgt]);
		else
			break ;
	}
	sort(tab, bg, rgt, f);
	sort(tab, rgt + 1, ed, f);
}

void			ft_sort_qck(void **tab, int size, int (*f)(void *, void *))
{
	sort(tab, 0, size - 1, f);
}
