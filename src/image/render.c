#include "minirt.h"

// t_rgb	pixel_colour(u_int32_t x, u_int32_t y, t_dt *dt)
// {
// 	t_rgb	colour;

// 	colour.r = (y * 255/ dt->screen_height) % 256;
// 	colour.g = (x * 255 / dt->screen_width) % 256;
// 	colour.b =  ((x + y) * 255  / (dt->screen_height + dt->screen_width)) % 256;
// 	return (colour);
// }

t_rgb	pixel_colour(u_int32_t x, u_int32_t y, t_dt *dt)
{
	t_rgb	colour;

	colour.r = (y * 255/ dt->screen_height) % 256;
	colour.g = (x * 255 / dt->screen_width) % 256;
	colour.b =  ((x + y) * 255  / (dt->screen_height + dt->screen_width)) % 256;
	return (colour);
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
	return (draw_image(dt));
}
