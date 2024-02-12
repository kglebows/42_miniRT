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

/*exit*/
t_ok		err(char *str);
t_ok		msg(char *str);

/*image*/
t_ok		render_mlx(t_dt *dt);
void		ini_viewport(t_vector c_dir, t_point c_pos, double fov, t_dt *dt);

/*math*/
t_vector	v_scale(t_vector vector, double scalar);
t_vector	v_add(t_vector vector1, t_vector vector2);
t_vector	v_subtract(t_vector vector1, t_vector vector2);
double		v_length(t_vector vector);
t_vector	v_normalize(t_vector vector);
double		v_dot(t_vector vector1, t_vector vector2);
t_vector	v_cross(t_vector vector1, t_vector vector2);
t_vector	v_translate(t_vector vector, t_point point);
t_point		p_translate(t_vector vector, t_point point);

#endif
