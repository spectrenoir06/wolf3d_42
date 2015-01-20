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
	double angle;

	angle = (vect.y + 1) / (vect.x);
	angle = atan(angle);
	return (angle * -2);
}

double		get_vect2dd_angles(t_vect2dd vect, t_vect2dd vect2)
{
	double angle;

	angle = (vect2.y - vect.y) / (vect2.x - vect.x);
	angle = atan(angle);
	return (angle);
}


t_vect2dd	angle_to_vect2dd(double angle)
{
	t_vect2dd vect;

	vect.x = 1;
	vect.y = 0;
	vect = vect2dd_rotate(vect, angle);
	return (vect);
}

int			did_vect2dd_cross(t_vect2dd start, t_vect2dd end)
{
	return (0);
}
