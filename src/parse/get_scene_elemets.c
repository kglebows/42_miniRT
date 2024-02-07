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
	scene->split = ft_split(scene->line, ' ');
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

	scene->split = ft_split(scene->line, ' ');
	split = ft_split(scene->split[2], ',');
	ft_bzero(&scene->ambilight, 0);
	if (ft_str_isfloat(scene->split[1]) && ft_arraylen(split) == 3)
	{
		ratio = ft_atof(scene->split[1]);
		scene->ambilight.ratio = ratio;
		get_rgb(scene, split);
	}
	else
		exit(2);
	if (new)
		return ;
}
