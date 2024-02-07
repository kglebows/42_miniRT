#include "minirt.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return(ft_putstr_fd("invalid nummber of aguments", 2), 1);
	t_scene scene;
	pars_scene(argv[1], &scene);
	printf("%d %d\n", scene.rgb.b,scene.rgb.r );
	return 0;
}
/*

NOTES FOR PARSING:

-> Normalize (use normalize function on provided vector) all axises before putting them inside of structures.
-> If Camera direction or any object direction is [0,0,0] -> throw an error
*/
