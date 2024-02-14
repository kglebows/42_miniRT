/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:35:48 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/14 13:07:20 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a camera ray for individual pixel
 * @param x pixel x position
 * @param y pixel y position
 * @param dt main data structure
 * @return ray between the camera and the pixel on (x,y)
*/
t_ray	r_pixelray(u_int32_t x, u_int32_t y, t_dt *dt)
{
	t_point		pixel;
	t_ray		ray;

	ray.o = dt->cam_pos;
	pixel = p_translate(v_add(
		v_scale(dt->delta_u, x),
		v_scale(dt->delta_v, y)),
		dt->pixel_center);
	ray.d = v_normalize(v_p2p(dt->cam_pos, pixel));
	return (ray);
}

t_rgb	ray_shot(t_ray ray, t_dt *dt)
{
	t_elem		*temp;
	t_hit		hit;
	t_hit		temp_hit;

	hit.type = BG;
	temp = dt->elements;
	while (temp != NULL)
	{
		if (temp->type == SP)
			temp_hit = ray_target_sphere(ray, temp, dt);
		else if (temp->type == PL)
			temp_hit = ray_target_plane(ray, temp, dt);
		else if (temp->type == CY)
			temp_hit = ray_target_cylinder(ray, temp, dt);
		else
			err("UNIDENTIFIED ELEMENT IN THE LIST!");
		if (temp_hit.type != BG 
			&& ((hit.type == BG && temp_hit.distance > 0)
			|| (hit.type != BG && temp_hit.distance < hit.distance)))
			hit = temp_hit;
		temp = temp->next;
	}
	return (light(hit, dt));
}

/**
 * @brief Gets a rgb colour for individual pixel.
 * If Super Sampling Anty Aliasing (SSAA) is enabled, shoots 5 rays:
 * to the center of a pixel and to the center of each side of a pixel
 * then aproximates the colour from these 5 rays
 * @param x pixel x position
 * @param y pixel y position
 * @param dt main data structure
 * @return rgb colour to draw pixel
*/
t_rgb	pixel_colour(u_int32_t x, u_int32_t y, t_dt *dt)
{
	t_rgb	rgb;
	t_rgb	ss[5];

	if (SSAA == 0)
		rgb = ray_shot(r_pixelray(x, y, dt), dt);
	else
	{
		ss[0] = ray_shot(r_pixelray(x, y, dt), dt);
		ss[1] = ray_shot(r_pixelray(x + 0.5, y, dt), dt);
		ss[2] = ray_shot(r_pixelray(x - 0.5, y, dt), dt);
		ss[3] = ray_shot(r_pixelray(x, y + 0.5, dt), dt);
		ss[4] = ray_shot(r_pixelray(x, y - 0.5, dt), dt);
		rgb.r = round((ss[0].r + ss[1].r + ss[2].r + ss[3].r + ss[4].r) / 5);
		rgb.g = round((ss[0].g + ss[1].g + ss[2].g + ss[3].g + ss[4].g) / 5);
		rgb.b = round((ss[0].b + ss[1].b + ss[2].b + ss[3].b + ss[4].b) / 5);
	}
	return (rgb);
}

/**
 * @brief Converts the RGB into 32bit int RGBA.
 * @param rgb Colour in 3x8bit RGB (0,0,0) - (255,255,255)
 * @param alpha Transparency in 1x8bit value. 0 - Transparent, 255 - fully opaque
 * @return 32bit RGBA
*/
u_int32_t	rgba2int(t_rgb rgb, uint32_t alpha)
{
	u_int32_t	rgba;

	rgba = alpha;
	rgba |= (u_int32_t)rgb.b << 8;
	rgba |= (u_int32_t)rgb.g << 16;
	rgba |= (u_int32_t)rgb.r << 24;
	return (rgba);
}

t_ok	draw_image(t_dt *dt)
{
	u_int32_t		x;
	u_int32_t		y;

	y = 0;
	while (y < dt->screen_height)
	{
		x = 0;
		while (x < dt->screen_width)
		{
			mlx_put_pixel(dt->img, x, y, rgba2int(pixel_colour(x, y, dt), 255));
			x++;
		}
		y++;
	}
	return (OK);
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
	mlx_image_to_window(dt->mlx, dt->img, 0, 0);
	ini_viewport((t_vector){0,0,-1}, (t_point){0,0,40}, 70, dt);
	ini_elements((t_point){0,0,40}, dt);
	return (draw_image(dt));
}
