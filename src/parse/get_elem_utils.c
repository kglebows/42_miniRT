/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:54 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/23 13:08:30 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	ft_strisint(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!ft_isdigit(str[i]) && str[i] != '\n')
			return (false);
		i++;
	}
	return (true);
}

bool	ft_str_isfloat(char *str)
{
	int	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (!(ft_isdigit(str[i]) == 1 || str[i] == '-' || str[i] == '+'
				|| str[i] == '.'))
			return (0);
		i++;
	}
	return (1);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	power;

	result = 0.0;
	sign = 1.0;
	power = 1.0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		result = result * 10.0 + (*str++ - '0');
	if (*str == '.')
	{
		str++;
		while (*str >= '0' && *str <= '9')
		{
			result = result * 10.0 + (*str++ - '0');
			power *= 10.0;
		}
		result /= power;
	}
	return (result * sign);
}

t_point	get_coord(char *attr)
{
	char	**split;
	t_point	coord;

	split = ft_split(attr, ',');
	if (ft_arraylen(split) != 3 || !(ft_str_isfloat(split[0])
			&& ft_str_isfloat(split[1]) && ft_str_isfloat(split[2])))
	{
		free_char_array(split);
		ft_putstr_fd("wrong coordinates", 2);
		exit(EXIT_FAILURE);
	}
	coord.x = ft_atof(split[0]);
	coord.y = ft_atof(split[1]);
	coord.z = ft_atof(split[2]);
	free_char_array(split);
	return (coord);
}
t_vector	get_vec_coord(char *attr)
{
	char		**split;
	t_vector	coord;

	split = ft_split(attr, ',');
	if (ft_arraylen(split) != 3 || !(ft_str_isfloat(split[0])
			&& ft_str_isfloat(split[1]) && ft_str_isfloat(split[2])))
	{
		ft_putstr_fd("Invalid vector1", 2);
		free_char_array(split);
		exit(EXIT_FAILURE);
	}
	coord.x = ft_atof(split[0]);
	coord.y = ft_atof(split[1]);
	coord.z = ft_atof(split[2]);
	free_char_array(split);
	return (coord);
}

double	get_ratio(char *str)
{
	double	nbr;

	nbr = ft_atof(str);
	if (!(nbr >= 0.0 && nbr <= 1.0))
	{
		ft_putstr_fd("Invalid ratio", 2);
		exit(EXIT_FAILURE);
	}
	return (nbr);
}
double	get_size(char *str)
{
	double	nbr;

	nbr = ft_atof(str);
	if (nbr < 0.0)
	{
		ft_putstr_fd("Invalid diameter size", 2);
		exit(EXIT_FAILURE);
	}
	return (nbr);
}

t_vector	get_normal(char *str)
{
	t_vector	coord;

	coord = get_vec_coord(str);
	printf("Center: (%f, %f, %f)", coord.x, coord.y, coord.z);
	if (coord.x >= -1.0 && coord.x <= 1.0 && coord.y >= -1.0 && coord.y <= 1.0
		&& coord.z >= -1.0 && coord.z <= 1.0 && coord.x != 0.0 && coord.y != 0.0
		&& coord.z != 0.0)
		return (coord);
	else
	{
		ft_putstr_fd("Invalid vector2", 2);
		exit(EXIT_FAILURE);
	}
}
