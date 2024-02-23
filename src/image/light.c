/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:23:07 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/23 11:18:47 by kglebows         ###   ########.fr       */
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
	//
	bg = (t_rgb){100, 100, 100};
	//
	return (bg);
}

t_rgb	light_specular(t_hit hit, t_ray ray, t_dt *dt)
{
	t_vector	reflect;
	double		specular;
	t_rgb		rgb;

	reflect = v_subtract(v_scale(hit.norm, 2 * d_dot(hit.norm, ray.d)), ray.d);
	hit.ray.d = v_scale(hit.ray.d, -1);
	specular = pow(fmax(d_dot(hit.ray.d, reflect) * -1 , 0), dt->shiness);
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
	// ray.o = hit.point;
	ray.d = v_normalize(v_scale(v_p2p(dt->l_pos, hit.point), 1));
	light = ray_shot(ray, dt);
	if (light.distance > 0 && hit.distance - light.distance < dt->cl_len + 0.000001)
	{
		diffuse = rgb_combine(hit.color, dt->l_rgb, d_dot(hit.norm, ray.d) * dt->l_ratio * -1);
		specular = light_specular(hit, ray, dt);
		// printf("norm:%f.%f.%f ", light.norm.x, light.norm.y, light.norm.z);
		// printf("ray:%f.%f.%f ", light.ray.d.x, light.ray.d.y, light.ray.d.z);
		// printf("color_motherfucker d%d:%d:%d\n", diffuse.r, diffuse.g, diffuse.b);
		// printf("color_motherfucker d%d:%d:%d s%d:%d:%d\n", diffuse.r, diffuse.g, diffuse.b, specular.r, specular.g, specular.b);
		// if (DIFFUSE == 1)
			ambient = rgb_add(ambient, diffuse);
		// if (SPECULAR == 1)
			ambient = rgb_add(ambient, specular);
	}
	return (ambient);
}
