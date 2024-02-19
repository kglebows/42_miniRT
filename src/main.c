#include "minirt.h"

t_scene	*initialize_scene(t_scene *scene)
{
    scene = ft_calloc(sizeof(t_scene), 1);

    // Initialize all fields to default or NULL values
    scene->line = NULL;
    scene->split = NULL;
    for (int i = 0; i < 9; i++) {
        scene->qtys[i] = 0;
    }
    // Initialize resol and ambilight (assuming they're also structures with fields to initialize)

	// scene->resol = initialize_resol(); // You need to define initialize_resol() appropriately
    // scene->ambilight = initialize_ambilight(); // You need to define initialize_ambilight() appropriately

    // // Initialize list pointers to NULL
    scene->cam = NULL;
    scene->light = NULL;
    scene->sp = NULL;
    scene->pl = NULL;
    scene->cy = NULL;

    return scene;
}



#include <stdio.h>
#include "struct.h" // Assuming your structure definitions are in a header file named struct.h

void print_scene(const t_scene *scene) {
    // Print resolution
    printf("Resolution: %dx%d\n", scene->resol.x, scene->resol.y);

    // Print ambilight
    printf("Ambilight Ratio: %lf\n", scene->ambilight.ratio);
    printf("Ambilight Color: R%d, G%d, B%d\n", scene->ambilight.rgb.r, scene->ambilight.rgb.g, scene->ambilight.rgb.b);

    // Print camera
    printf("Camera Position: (%lf, %lf, %lf)\n", scene->cam->point.x, scene->cam->point.y, scene->cam->point.z);
    printf("Camera Normal: (%lf, %lf, %lf)\n", scene->cam->normal.x, scene->cam->normal.y, scene->cam->normal.z);
    printf("Camera FOV: %f\n", scene->cam->fov);

    // Print elements: light
    printf("Lights:\n");
    t_elem *current_light = scene->light;
    while (current_light != NULL) {
        printf("  Element Type: %d\n", current_light->type);
        printf("  Element Center: (%lf, %lf, %lf)\n", current_light->center.x, current_light->center.y, current_light->center.z);
        // Print other attributes of the light element as needed
        current_light = current_light->next;
    }

    // Print elements: sp
    printf("Spheres:\n");
    t_elem *current_sp = scene->sp;
    while (current_sp != NULL) {
        printf("  Element Type: %d\n", current_sp->type);
        printf("  Element Center: (%lf, %lf, %lf)\n", current_sp->center.x, current_sp->center.y, current_sp->center.z);
        // Print other attributes of the sphere element as needed
        current_sp = current_sp->next;
    }

    // Print elements: pl
    printf("Planes:\n");
    t_elem *current_pl = scene->pl;
    while (current_pl != NULL) {
        printf("  Element Type: %d\n", current_pl->type);
        printf("  Element Center: (%lf, %lf, %lf)\n", current_pl->center.x, current_pl->center.y, current_pl->center.z);
        // Print other attributes of the plane element as needed
        current_pl = current_pl->next;
    }


    // Print elements: cy
    printf("Cylinders:\n");
    t_elem *current_cy = scene->cy;
    while (current_cy != NULL) {
        printf("  Element Type: %d\n", current_cy->type);
        printf("  Element Center: (%lf, %lf, %lf)\n", current_cy->center.x, current_cy->center.y, current_cy->center.z);
        // Print other attributes of the cylinder element as needed
        current_cy = current_cy->next;
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
-> If Camera direction or any object direction is [0,0,0] -> throw an error
*/
