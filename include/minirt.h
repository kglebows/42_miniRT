#ifndef MINIRT_H
# define MINIRT_H

# include <unistd.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include "../lib/libft/libft.h"
# include "../lib/mlx/include/MLX42/MLX42.h"
# include "struct.h"

# ifndef SSAA
#  define SSAA 0
# endif

# ifndef SPECULAR
#  define SPECULAR 1
# endif

# ifndef DIFFUSE
#  define DIFFUSE 0
# endif

/*exit*/
t_ok		err(char *str);
t_ok		msg(char *str);

/*image*/
t_ok		render_mlx(t_dt *dt);
void		ini_dt(t_dt *dt);
void		ini_viewport(t_dt *dt);
void		ini_elements(t_dt *dt);
t_hit		ray_target_sphere(t_ray ray, t_elem *element, t_dt *dt);
t_hit		ray_target_plane(t_ray ray, t_elem *element, t_dt *dt);
t_hit		ray_target_cylinder(t_ray ray, t_elem *element, t_dt *dt);
t_hit		ray_shot(t_ray ray, t_dt *dt);
t_rgb		light(t_hit hit, t_dt *dt);

/*math*/
t_vector	v_scale(t_vector vector, double scalar);
t_vector	v_add(t_vector vector1, t_vector vector2);
t_vector	v_subtract(t_vector vector1, t_vector vector2);
double		d_length(t_vector vector);
t_vector	v_normalize(t_vector vector);
double		d_dot(t_vector vector1, t_vector vector2);
t_vector	v_cross(t_vector vector1, t_vector vector2);
t_vector	v_translate(t_vector vector, t_point point);
t_point		p_translate(t_vector vector, t_point point);
t_vector	v_p2p(t_point start, t_point end);
t_qf		quadratic_formula(double a, double b, double c);
double		d_shortest_distance(t_qf qf);
t_rgb		rgb_add(t_rgb base, t_rgb add);
t_rgb		rgb_combine(t_rgb base, t_rgb combine, double ratio);
t_rgb		rgb_scale(t_rgb base, double ratio);

#endif
