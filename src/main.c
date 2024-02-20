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
	scene->sp = NULL;
	scene->pl = NULL;
	scene->cy = NULL;
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
    printf("Spheres:\n");
    t_elem *sp = scene->sp;
    while (sp != NULL) {
        printf("Center: (%f, %f, %f), Diameter: %f, Color: %d, %d, %d\n", sp->center.x, sp->center.y, sp->center.z,
               sp->diameter, sp->color.r, sp->color.g, sp->color.b);
        sp = sp->next;
    }

    // Print plane elements
    printf("Planes:\n");
    t_elem *pl = scene->pl;
    while (pl != NULL) {
        printf("Center: (%f, %f, %f), Axis: (%f, %f, %f), Color: %d, %d, %d\n", pl->center.x, pl->center.y, pl->center.z,
               pl->axis.x, pl->axis.y, pl->axis.z, pl->color.r, pl->color.g, pl->color.b);
        pl = pl->next;
    }

	// Print cylinder elements
	printf("Cylinders:\n");
	t_elem *cy = scene->cy;
	while (cy != NULL) {
	    printf("Center: (%f, %f, %f), Axis: (%f, %f, %f), Diameter: %f, Height: %f, Color: %d, %d, %d\n",
	           cy->center.x, cy->center.y, cy->center.z, cy->axis.x, cy->axis.y, cy->axis.z,
	           cy->diameter, cy->height, cy->color.r, cy->color.g, cy->color.b);
	    cy = cy->next;
}
}





int main(int argc, char **argv)
{
	if (argc != 2)
		return(ft_putstr_fd("invalid nummber of aguments", 2), 1);
	t_scene *scene = NULL;
	scene = initialize_scene(scene);
	pars_scene(argv[1], scene);
	print_scene(scene);
	return 0;
}
/*

NOTES FOR PARSING:

-> Normalize (use normalize function on provided vector) all axises before putting them inside of structures.
*/
