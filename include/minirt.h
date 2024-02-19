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
void	get_resol(t_scene *scene);
t_point	get_coord(char *attr);
void	get_camera(t_scene *scene);
void get_light(t_scene *scene);
t_vector	get_normal(char *str);
void get_sp(t_scene *scene);

void get_pl(t_scene *scene);

void get_cy(t_scene *scene);


double get_ratio(char *str);
double	get_size(char *str);

bool	ft_strisint(char *str);
bool	ft_str_isfloat(char *str);

void	get_ambilight(t_scene *scene);
double	ft_atof(const char *str);

double	ft_atof(const char *str);
size_t	ft_arraylen(char **s);
t_rgb	get_rgb(char *split);
bool	ft_isrgb(int n);
t_vector get_vec_coord(char *attr);

void	free_char_array(char **array);
t_point		gen_coord(double x, double y, double z);
void	t_elem_add_back(t_elem **lst, t_elem *new);
void	t_cam_add_back(t_cam **lst, t_cam *new);


#endif
