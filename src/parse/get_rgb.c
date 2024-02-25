/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:04:58 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/24 16:18:44 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_isrgb(int n)
{
	if (n >= 0 && n <= 255)
		return (true);
	return (false);
}

t_rgb	get_rgb(t_scene *scene, char *rgb)
{
	t_rgb	temp;
	char	**split;
	int		i;

	split = ft_split(rgb, ',');
	i = 0;
	ft_bzero(&temp, 0);
	while (i < 3)
	{
		if (ft_strisint(split[i]) == false
			|| ft_isrgb(ft_atoi(split[i])) == false)
		{
			err("Invalid RGB color");
			free_char_array(split);
			ft_exit(scene);
		}
		i++;
	}
	temp.r = ft_atoi(split[0]);
	temp.g = ft_atoi(split[1]);
	temp.b = ft_atoi(split[2]);
	free_char_array(split);
	return (temp);
}
