#ifndef MINIRT_H
# define MINIRT_H

# include "../lib/libft/libft.h"
# include "math.h"
# include "struct.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <unistd.h>

void	pars_scene(char *file, t_scene *scene);
void	get_resol(t_scene *scene, t_elem **new);
t_point	get_coord(char *attr);
void	get_camera(t_scene *scene, t_elem **new);
void get_light(t_scene *scene, t_elem **new);
t_point	get_normal(char *str);

double get_ratio(char *str);
double	get_size(char *str);

bool	ft_strisint(char *str);
bool	ft_str_isfloat(char *str);

void	get_ambilight(t_scene *scene, t_elem **new);
double	ft_atof(const char *str);

double	ft_atof(const char *str);
size_t	ft_arraylen(char **s);
void	get_rgb(t_scene *scene, char **split);
bool	ft_isrgb(int n);

void	free_char_array(char **array);


#endif
