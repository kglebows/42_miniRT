/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:23:07 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/22 15:25:13 by kglebows         ###   ########.fr       */
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

t_rgb	light_specular(t_hit hit, t_ray ray, t_dt *dt)
{
	t_vector	reflect;
	double		specular;
	t_rgb		rgb;

	reflect = v_subtract(v_scale(hit.norm, 2 * d_dot(hit.norm, ray.d)), ray.d);
	hit.ray.d = v_scale(hit.ray.d, -1);
	specular = pow(fmax(d_dot(hit.ray.d, reflect) , 0), dt->shiness);
	rgb = rgb_scale(dt->l_rgb, specular * dt->l_ratio);
	return (rgb);
}

t_rgb	light(t_hit hit, t_dt *dt)
{
	t_rgb		ambient;
	t_rgb		diffuse;
	t_rgb		specular;
	t_ray		ray;
	t_hit		light;

	if (hit.type == BG)
		return (background(hit, dt));
	ambient = rgb_combine(hit.color, dt->a_rgb, dt->a_ratio);
	ray.o = dt->l_pos;
	ray.d = v_normalize(v_p2p(ray.o, hit.point));
	light = ray_shot(ray, dt);
	if (hit.type == light.type && hit.distance - light.distance < dt->cl_len)
	{
		diffuse = rgb_scale(dt->l_rgb, d_dot(hit.norm, ray.d) * dt->l_ratio);
		specular = light_specular(hit, ray, dt);
		if (DIFFUSE)
			ambient = rgb_add(ambient, diffuse);
		if (SPECULAR)
			ambient = rgb_add(ambient, specular);
	}
	return (ambient);
}
