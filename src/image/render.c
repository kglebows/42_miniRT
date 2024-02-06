#include "minirt.h"

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


}
