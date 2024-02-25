/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_scene_elemets1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:51:03 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/24 16:34:43 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_sp(t_scene *scene, t_dt *dt)
{
	t_elem	*temp;

	(void)dt;
	temp = (t_elem *)malloc(sizeof(t_elem));
	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene, scene->split[1]);
	temp->diameter = get_size(scene, scene->split[2]);
	temp->color = get_rgb(scene, scene->split[3]);
	temp->type = SP;
	t_elem_add_back(&scene->elements, temp);
}

void	get_pl(t_scene *scene, t_dt *dt)
{
	t_elem	*temp;

	(void)dt;
	temp = (t_elem *)malloc(sizeof(t_elem));
	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene, scene->split[1]);
	temp->axis = get_vec_coord(scene, scene->split[2]);
	temp->color = get_rgb(scene, scene->split[3]);
	temp->type = PL;
	t_elem_add_back(&scene->elements, temp);
}

void	get_cy(t_scene *scene, t_dt *dt)
{
	t_elem	*temp;

	(void)dt;
	temp = (t_elem *)malloc(sizeof(t_elem));
	ft_bzero(temp, sizeof(t_elem));
	temp->center = get_coord(scene, scene->split[1]);
	temp->axis = get_vec_coord(scene, scene->split[2]);
	temp->diameter = get_size(scene, scene->split[3]);
	temp->height = get_size(scene, scene->split[4]);
	temp->color = get_rgb(scene, scene->split[5]);
	temp->type = CY;
	t_elem_add_back(&scene->elements, temp);
}
