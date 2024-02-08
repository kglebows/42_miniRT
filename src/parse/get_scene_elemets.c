/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elemets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:56:19 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/07 16:10:10 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_resol(t_scene *scene, t_elem **new)
{
	if (ft_strisint(scene->split[1]) && ft_strisint(scene->split[2]))
	{
		scene->resol.x = ft_atoi(scene->split[1]);
		scene->resol.y = ft_atoi(scene->split[2]);
	}
	else
	{
		printf("noo");
		exit(1);
	}
	if (new)
		return ;
}

void	get_ambilight(t_scene *scene, t_elem **new)
{
	double	ratio;
	char	**split;

	split = ft_split(scene->split[2], ',');
	ft_bzero(&scene->ambilight, 0);
	if (ft_str_isfloat(scene->split[1]) && ft_arraylen(split) == 3)
	{
		ratio = ft_atof(scene->split[1]);
		scene->ambilight.ratio = ratio;
		get_rgb(scene, split);
		free_char_array(split);
	}
	else
	{
		exit(2);
		free_char_array(split);
	}
	if (new)
		return ;
}

void get_camera(t_scene *scene, t_elem **new)
{
	t_cam	*tmp;

	free(*new);
	tmp = (t_cam*)malloc(sizeof(t_cam));
	ft_bzero(tmp, sizeof(t_cam));
	tmp->point = get_coord(scene->split[1]);
	tmp->normal = get_coord(scene->split[3]);
	tmp->fov = ft_atof(scene->split[2]);
	ft_lstadd_back(scene->cam, tmp);
	scene->qtys[2]++;
}

void get_light(t_scene *scene, t_elem **new)
{
	t_elem *temp;

	ft_bzero(temp, sizeof(t_elem));
	temp->point = get_coord(scene->split[1]);
	temp->ratio = get_ratio(scene->split[2]);
	temp->color = get_color(scene->split[3]);
	ft_lstadd_back(scene->light, temp);
}

void get_sp(t_scene *scene, t_elem **new)
{
	t_elem *temp;

	ft_bzero(temp, sizeof(t_elem));
	temp->point = get_coord(scene->split[1]);
	temp->diam = get_size(scene->split[2]);
	temp->color = get_color(scene->split[3]);
	ft_lstadd_back(scene->sp, temp);
}

void get_pl(t_scene *scene, t_elem **new)
{
	t_elem *temp;

	ft_bzero(temp, sizeof(t_elem));
	temp->point = get_coord(scene->split[1]);
	temp->normal = get_normal(scene->split[2]);
	temp->color = get_color(scene->split[3]);
	ft_lstadd_back(scene->pl, temp);
}
