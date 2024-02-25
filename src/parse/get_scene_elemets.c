/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elemets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:56:19 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/25 12:02:43 by kglebows         ###   ########.fr       */
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
	dt->c_dir = get_vec_coord(scene, scene->split[2]);
	if (dt->c_dir.x == 0 && dt->c_dir.y == 0 && dt->c_dir.z == 0)
	{
		err("Invalid camera direction");
		ft_exit(scene);
	}
	dt->c_dir = v_normalize(dt->c_dir);
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
