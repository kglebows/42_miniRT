/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elemets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:56:19 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/24 19:08:56 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_ambilight(t_scene *scene, t_dt *dt)
{
	char	**split;

	split = ft_split(scene->split[2], ',');
	if (ft_str_isfloat(scene->split[1]) && ft_arraylen(split) == 3)
	{
		dt->a_ratio = get_ratio(scene, scene->split[1]);
		dt->a_rgb = get_rgb(scene, scene->split[2]);
		free_char_array(split);
	}
	else
	{
		free_char_array(split);
		err("Invalid ambilight");
		ft_exit(scene);
	}
}

void	get_camera(t_scene *scene, t_dt *dt)
{
	dt->c_pos = get_coord(scene, scene->split[1]);
	dt->c_dir = v_normalize(get_vec_coord(scene, scene->split[2]));
	dt->c_fov = ft_atof(scene, scene->split[3]);
	if (dt->c_fov < 0 || dt->c_fov > 180)
	{
		err("Invalid camera fov value");
		ft_exit(scene);
	}
}

void	get_light(t_scene *scene, t_dt *dt)
{
	dt->l_pos = get_coord(scene, scene->split[1]);
	dt->l_ratio = get_ratio(scene, scene->split[2]);
	dt->l_rgb = get_rgb(scene, scene->split[3]);
}
