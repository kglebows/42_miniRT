#include "minirt.h"

int main(int argc, char **argv)
{
	t_dt	dt;


	if (argc != 2)
		return(ft_putstr_fd("invalid nummber of aguments", 2), 1);
	// t_scene scene;
	(void)argv;
	render_mlx(&dt);
	// pars_scene(argv[1], &scene);
	// printf("%d %d\n", scene.resol.x, scene.resol.y);
	return 0;
}
/*

NOTES FOR PARSING:

-> Normalize (use normalize function on provided vector) all axises before putting them inside of structures.
-> If Camera direction or any object direction is [0,0,0] -> throw an error
*/
