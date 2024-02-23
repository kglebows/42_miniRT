#include "minirt.h"

t_scene	*initialize_scene(t_scene *scene)
{
	int i;

	i = 0;
	scene = ft_calloc(sizeof(t_scene), 1);
	scene->line = NULL;
	scene->split = NULL;
	while (i < 9)
		scene->qtys[i++] = 0;
	scene->cam = NULL;
	scene->light = NULL;
	scene->elements = NULL;
	return scene;
}


void print_scene(const t_scene *scene) {
    printf("Resolution: %d x %d\n", scene->resol.x, scene->resol.y);
    printf("Ambilight ratio: %f\n", scene->ambilight.ratio);
    printf("Ambilight RGB: %d, %d, %d\n", scene->ambilight.rgb.r, scene->ambilight.rgb.g, scene->ambilight.rgb.b);

    // Print camera information
    printf("Cameras:\n");
    t_cam *cam = scene->cam;
    while (cam != NULL) {
        printf("Point: (%f, %f, %f), Normal: (%f, %f, %f), FOV: %f\n", cam->point.x, cam->point.y, cam->point.z,
               cam->normal.x, cam->normal.y, cam->normal.z, cam->fov);
        cam = cam->next;
    }

    // Print light elements
    printf("Lights:\n");
    t_elem *light = scene->light;
    while (light != NULL) {
        printf("Center: (%f, %f, %f), Ratio: %f, Color: %d, %d, %d\n", light->center.x, light->center.y, light->center.z,
               light->ratio, light->color.r, light->color.g, light->color.b);
        light = light->next;
    }

    // Print sphere elements
    printf("ELEMENTS:\n");
    t_elem *sp = scene->elements;
    while (sp != NULL)
	{
		if (sp->type == SP)
		{
			printf("SP || Center: (%f, %f, %f), Diameter: %f, Color: %d, %d, %d\n", sp->center.x, sp->center.y, sp->center.z,
				sp->diameter, sp->color.r, sp->color.g, sp->color.b);
		}
		if (sp->type == PL)
		{
			printf("PL || Center: (%f, %f, %f), Axis: (%f, %f, %f), Color: %d, %d, %d\n", sp->center.x, sp->center.y, sp->center.z,
				sp->axis.x, sp->axis.y, sp->axis.z, sp->color.r, sp->color.g, sp->color.b);
		}
		if (sp->type == CY)
		{
			printf("CY || Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f, Color: %d, %d, %d\n",
				sp->center.x, sp->center.y, sp->center.z, sp->axis.x, sp->axis.y, sp->axis.z,
				sp->diameter, sp->height, sp->color.r, sp->color.g, sp->color.b);
		}
			sp = sp->next;
    }

//     // Print spane elements
//     printf("Planes:\n");
//     t_elem *pl = scene->pl;
//     while (pl != NULL) {
//         pl = pl->next;
//     }

// 	// Print cylinder elements
// 	printf("Cylinders:\n");
// 	t_elem *cy = scene->cy;
// 	while (cy != NULL) {
// 	    cy = cy->next;
// }
}





int main(int argc, char **argv)
{
	t_dt	dt;
	t_scene	*scene = NULL;

	if (argc != 2)
		return(ft_putstr_fd("invalid nummber of aguments", 2), 1);
	scene = initialize_scene(scene);
	dt.scene = scene;
	pars_scene(argv[1], scene);
	printf("hello\n");
	print_scene(scene);
	// render_mlx(&dt);
	// mlx_loop(dt.mlx);
	return 0;
}
