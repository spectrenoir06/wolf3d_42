/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoussau <antoine@doussaud.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/15 21:45:47 by adoussau          #+#    #+#             */
/*   Updated: 2015/01/15 21:45:47 by adoussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <math.h>

t_vect2dd	vect2dd_rotate(t_vect2dd vect, double angle)
{
	t_vect2dd	new;

	new.x = vect.x * cos(angle) - vect.y * sin(angle);
	new.y = vect.x * sin(angle) + vect.y * cos(angle);
	return (new);
}

int			did_vect2dd_cross(t_vect2dd start, t_vect2dd end)
{
	return (0);
}
