/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:04:58 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/18 20:08:47 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_isrgb(int n)
{
	if (n >= 0 && n <= 255)
		return (true);
	return (false);
}
t_rgb	get_rgb(char *rgb)
{
	t_rgb temp;
	char **split = ft_split(rgb, ',');
	int	i;

	i = 0;
	ft_bzero(&temp, 0);
	while (i < 3)
	{
		if (ft_strisint(split[i]) == false)
			exit(3);
		if (ft_isrgb(ft_atoi(split[i])) == false)
			exit(3);
		i++;
	}
	temp.r = ft_atoi(split[0]);
	temp.g = ft_atoi(split[1]);
	temp.b = ft_atoi(split[2]);
	return(temp);
}
