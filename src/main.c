#include "minirt.h"

t_scene	*initialize(t_scene *scene, t_dt *dt)
{
	int	i;

	i = 0;
	scene = ft_calloc(sizeof(t_scene), 1);
	scene->line = NULL;
	scene->split = NULL;
	while (i < 9)
		scene->qtys[i++] = 0;
	dt->a_ratio = 0.0;
	dt->a_rgb = get_rgb(scene, "0,0,0");
	dt->l_pos = get_coord(scene, "0,0,0");
	dt->l_ratio = 0.0;
	dt->l_rgb = get_rgb(scene, "0,0,0");
	scene->elements = NULL;
	return (scene);
}

int	main(int argc, char **argv)
{
	t_dt	dt;
	t_scene	*scene;

	scene = NULL;
	if (argc != 2)
		return (ft_putstr_fd("invalid nummber of aguments", 2), 1);
	scene = initialize(scene, &dt);
	dt.scene = scene;
	pars_scene(argv[1], scene, &dt);
	if (render_mlx(&dt) == KO)
		exit_win(&dt);
	free_elements(&dt);
	mlx_loop(dt.mlx);
	return 0;
}
