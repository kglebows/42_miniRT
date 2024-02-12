/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   viewport.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 14:44:14 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/12 17:09:42 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_upperleftpixelcenter(t_vector camera, t_point c_pos, t_dt *dt)
{
	t_vector	to_left_upper_corner;

	to_left_upper_corner = v_add(camera,
		v_scale(dt->delta_u, dt->screen_width * -0.5));
	to_left_upper_corner = v_add(to_left_upper_corner,
		v_scale(dt->delta_v, dt->screen_height * -0.5));
	to_left_upper_corner = v_add(to_left_upper_corner,
		v_scale(dt->delta_u, 0.5));
	to_left_upper_corner = v_add(to_left_upper_corner,
		v_scale(dt->delta_v, 0.5));
	return (p_translate(to_left_upper_corner, c_pos));
}

void	ini_viewport(t_vector c_dir, t_point c_pos, double fov, t_dt *dt)
{
	double		focal_length;
	t_vector	camera;

	focal_length = dt->screen_width / (2 * tan((fov * (M_PI / 180)) / 2));
	camera = v_scale(c_dir, focal_length);
	if ((c_dir.x == 1 || c_dir.x == -1) && c_dir.y == 0 && c_dir.z == 0)
		dt->delta_v = v_normalize(v_cross((t_vector){0, 0, 1}, camera));
	else
		dt->delta_v = v_normalize(v_cross((t_vector){1, 0, 0}, camera));
	dt->delta_u = v_normalize(v_cross(camera, dt->delta_v));
	dt->pixel_center = get_upperleftpixelcenter(camera, c_pos, dt);
}
