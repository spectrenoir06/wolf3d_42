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

double		get_vect2dd_angle(t_vect2dd vect)
{
	double	angle;

	angle = (vect.y + 1) / (vect.x);
	angle = atan(angle);
	return (angle * -2);
}
