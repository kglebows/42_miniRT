/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:23:07 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/21 11:49:17 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	background(t_hit hit, t_dt *dt)
{
	t_rgb	bg;
	t_rgb	blend;
	double	ratio;

	blend = (t_rgb){255 - dt->bg.r , 255 - dt->bg.g, 255 - dt->bg.b};
	ratio = (hit.ray.d.y + 1) / 2;
	bg.r = 255 - round(blend.r * ratio);
	bg.g = 255 - round(blend.g * ratio);
	bg.b = 255 - round(blend.b * ratio);
	return (bg);
}

t_rgb	light(t_hit hit, t_dt *dt)
{
	t_rgb		rgb;

	if (hit.type == BG)
		return (background(hit, dt));
	rgb = rgb_combine(hit.color, dt->)
}
