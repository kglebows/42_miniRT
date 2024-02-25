/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 08:35:48 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:28:54 by kglebows         ###   ########.fr       */
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

	ray.o = dt->c_pos;
	pixel = p_translate(v_add(
				v_scale(dt->delta_u, x),
				v_scale(dt->delta_v, y)),
			dt->pixel_center);
	ray.d = v_normalize(v_p2p(dt->c_pos, pixel));
	return (ray);
}

t_hit	ray_shot(t_ray ray, t_dt *dt)
{
	t_elem		*temp;
	t_hit		hit;
	t_hit		temp_hit;

	hit.type = BG;
	hit.ray = ray;
	temp = dt->elements;
	while (temp != NULL)
	{
		if (temp->type == SP)
			temp_hit = ray_target_sphere(ray, temp);
		else if (temp->type == PL)
			temp_hit = ray_target_plane(ray, temp);
		else if (temp->type == CY)
			temp_hit = ray_target_cylinder(ray, temp);
		else
			err("UNIDENTIFIED ELEMENT IN THE LIST!");
		if (temp_hit.type != BG
			&& ((hit.type == BG && temp_hit.distance > 0)
				|| (hit.type != BG && temp_hit.distance < hit.distance
					&& temp_hit.distance > 0)))
			hit = temp_hit;
		temp = temp->next;
	}
	return (hit);
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

	if (SSAA <= 0)
		rgb = light(ray_shot(r_pixelray(x, y, dt), dt), dt);
	else
	{
		ss[0] = light(ray_shot(r_pixelray(x, y, dt), dt), dt);
		ss[1] = light(ray_shot(r_pixelray(x + 1, y, dt), dt), dt);
		ss[2] = light(ray_shot(r_pixelray(x - 1, y, dt), dt), dt);
		ss[3] = light(ray_shot(r_pixelray(x, y + 1, dt), dt), dt);
		ss[4] = light(ray_shot(r_pixelray(x, y - 1, dt), dt), dt);
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
