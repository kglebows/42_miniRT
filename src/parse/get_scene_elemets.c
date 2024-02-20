/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elemets.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:56:19 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/20 11:52:06 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_resol(t_scene *scene)
{
	if (ft_strisint(scene->split[1]) && ft_strisint(scene->split[2]))
	{
		scene->resol.x = ft_atoi(scene->split[1]);
		scene->resol.y = ft_atoi(scene->split[2]);
	}
	else
		exit(1);
}

void	get_ambilight(t_scene *scene)
{
	double	ratio;
	char	**split;


	split = ft_split(scene->split[2], ',');
	ft_bzero(&scene->ambilight, 0);
	if (ft_str_isfloat(scene->split[1]) && ft_arraylen(split) == 3)
	{
		ratio = ft_atof(scene->split[1]);
		scene->ambilight.ratio = ratio;
		scene->ambilight.rgb = get_rgb(scene->split[2]);
		free_char_array(split);
	}
	else
	{
		exit(2);
		free_char_array(split);
	}
}

void get_camera(t_scene *scene)
{
	t_cam	*tmp;

	tmp = (t_cam*)malloc(sizeof(t_cam));
	ft_bzero(tmp, sizeof(t_cam));
	tmp->point = get_coord(scene->split[1]);
	tmp->normal = get_coord(scene->split[2]);
	tmp->fov = ft_atof(scene->split[3]);
	t_cam_add_back(&scene->cam, tmp);
	scene->qtys[2]++;
}

void get_light(t_scene *scene)
{
	t_elem *temp;

	temp = (t_elem*)malloc(sizeof(t_elem));
	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene->split[1]);
	temp->ratio = get_ratio(scene->split[2]);
	temp->color = get_rgb(scene->split[3]);
	t_elem_add_back(&scene->light, temp);
}

void get_sp(t_scene *scene)
{
	t_elem *temp;

	temp = (t_elem*)malloc(sizeof(t_elem));

	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene->split[1]);
	temp->diameter = get_size(scene->split[2]);
	temp->color = get_rgb(scene->split[3]);
	temp->type = SP;
	t_elem_add_back(&scene->sp, temp);
}

void get_pl(t_scene *scene)
{
	t_elem *temp;

	temp = (t_elem*)malloc(sizeof(t_elem));

	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene->split[1]);
	temp->axis = get_normal(scene->split[2]);
	temp->color = get_rgb(scene->split[3]);
	temp->type = PL;
	t_elem_add_back(&scene->pl, temp);
}
void get_cy(t_scene *scene)
{
	t_elem *temp;

	temp = (t_elem*)malloc(sizeof(t_elem));

	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene->split[1]);
	temp->axis = get_normal(scene->split[2]);
	temp->diameter = get_size(scene->split[3]);
	temp->height = get_size(scene->split[4]);
	temp->color = get_rgb(scene->split[5]);
	temp->type = CY;
	t_elem_add_back(&scene->cy, temp);
}

