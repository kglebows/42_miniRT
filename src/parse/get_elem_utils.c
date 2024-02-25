/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:54 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/25 12:14:40 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point	get_coord(t_scene *scene, char *attr)
{
	char	**split;
	t_point	coord;

	split = ft_split(attr, ',');
	if (ft_arraylen(split) != 3 || !(ft_str_isfloat(split[0])
			&& ft_str_isfloat(split[1]) && ft_str_isfloat(split[2])))
	{
		free_char_array(split);
		err("Wrong coordinates");
		ft_exit(scene);
	}
	coord.x = ft_atof(scene, split[0]);
	coord.y = ft_atof(scene, split[1]);
	coord.z = ft_atof(scene, split[2]);
	free_char_array(split);
	return (coord);
}

t_vector	get_vec_coord(t_scene *scene, char *attr)
{
	char		**split;
	t_vector	coord;

	split = ft_split(attr, ',');
	if (ft_arraylen(split) != 3 || !(ft_str_isfloat(split[0])
			&& ft_str_isfloat(split[1]) && ft_str_isfloat(split[2])))
	{
		err("Invalid vector");
		free_char_array(split);
		ft_exit(scene);
	}
	coord.x = ft_atof(scene, split[0]);
	coord.y = ft_atof(scene, split[1]);
	coord.z = ft_atof(scene, split[2]);
	free_char_array(split);
	return (coord);
}

bool	ftstrisdouble(const char *str)
{
	bool	has_digits;

	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	has_digits = false;
	while (ft_isdigit(*str))
	{
		has_digits = true;
		str++;
	}
	if (*str == '.')
	{
		++str;
		while (ft_isdigit(*str))
		{
			has_digits = true;
			str++;
		}
	}
	return (has_digits && *str == '\0');
}

double	get_ratio(t_scene *scene, char *str)
{
	double	nbr;

	if (!ftstrisdouble(str))
	{
		err("Invalid ratio");
		ft_exit(scene);
	}
	nbr = ft_atof(scene, str);
	if (!(nbr >= 0.0 && nbr <= 1.0))
	{
		err("Invalid ratio range");
		ft_exit(scene);
	}
	return (nbr);
}

double	get_size(t_scene *scene, char *str)
{
	double	nbr;

	nbr = ft_atof(scene, str);
	if (nbr <= 0.0)
	{
		err("Invalid diameter size");
		ft_exit(scene);
	}
	return (nbr);
}
