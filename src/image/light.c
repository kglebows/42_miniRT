/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 10:23:07 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:30:49 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	background(t_hit hit, t_dt *dt)
{
	t_rgb		bg;
	double		ratio;
	t_rgb		top;
	t_rgb		bot;

	top = (t_rgb){255, 0, 0};
	bot = (t_rgb){0, 0, 255};
	ratio = (hit.ray.d.y + 1) * 0.5;
	bg.r = (1 - ratio) * top.r + bot.r * ratio;
	bg.g = (1 - ratio) * top.g + bot.g * ratio;
	bg.b = (1 - ratio) * top.b + bot.b * ratio;
	if (dt->c_fov == 0)
		return ((t_rgb){0, 0, 0});
	return (bg);
}

t_rgb	light_specular(t_hit hit, t_ray ray, t_dt *dt)
{
	t_vector	reflect;
	double		specular;
	t_rgb		rgb;

	reflect = v_subtract(v_scale(hit.norm, 2 * d_dot(hit.norm, ray.d)), ray.d);
	specular = pow(fmax(d_dot(v_scale(hit.ray.d, -1), reflect) * -1, 0),
			dt->shiness);
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
	ray.d = v_normalize(v_scale(v_p2p(dt->l_pos, hit.point), 1));
	light = ray_shot(ray, dt);
	if (light.distance > 0
		&& d_length(v_p2p(light.point, hit.point)) < 0.000001)
	{
		diffuse = rgb_combine(hit.color, dt->l_rgb,
				d_dot(hit.norm, ray.d) * dt->l_ratio * -1);
		specular = light_specular(hit, ray, dt);
		if (DIFFUSE == 1)
			ambient = rgb_add(ambient, diffuse);
		if (SPECULAR == 1)
			ambient = rgb_add(ambient, specular);
	}
	return (ambient);
}

t_ok	render_mlx(t_dt *dt)
{
	dt->screen_width = 1920;
	dt->screen_height = 1080;
	dt->mlx = mlx_init(dt->screen_width, dt->screen_height, "-=MiniRT=-", true);
	if (!dt->mlx)
		return (err("mlx initialization failed!"));
	dt->img = mlx_new_image(dt->mlx, dt->screen_width, dt->screen_height);
	if (!dt->img)
		return (err("mlx image creation failed!"));
	mlx_key_hook(dt->mlx, (void *)exit_esc, (void *)dt);
	mlx_close_hook(dt->mlx, (void *)exit_win, (void *)dt);
	mlx_image_to_window(dt->mlx, dt->img, 0, 0);
	ini_dt(dt);
	ini_viewport(dt);
	ini_elements(dt);
	return (draw_image(dt));
}
