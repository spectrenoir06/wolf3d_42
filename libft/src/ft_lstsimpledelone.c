/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsimpledelone.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/16 16:29:12 by adoussau          #+#    #+#             */
/*   Updated: 2014/11/16 16:30:13 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstsimpledelone(t_list **alst)
{
	if (*alst)
	{
		free(*alst);
		*alst = NULL;
	}
}
