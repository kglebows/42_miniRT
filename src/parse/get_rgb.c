/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:04:58 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/07 11:04:58 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_isrgb(int n)
{
	if (n >= 0 && n <= 255)
		return (true);
	return (false);
}
void	get_rgb(t_scene *scene, char **split)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (ft_strisint(split[i]) == false)
			exit(3);
		if (ft_isrgb(ft_atoi(split[i])) == false)
			exit(3);
	}
		scene->rgb.r = ft_atoi(split[1]);
		scene->rgb.g = ft_atoi(split[2]);
		scene->rgb.b = ft_atoi(split[3]);
}
