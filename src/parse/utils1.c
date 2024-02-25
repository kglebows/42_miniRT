/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:40:50 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/24 16:57:01 by ekordi           ###   ########.fr       */
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

double	parse_integer_part(char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

double	parse_decimal_part(char **str, double *power)
{
	double	result;

	result = 0.0;
	if (**str == '.')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			result = result * 10.0 + (**str - '0');
			*power *= 10.0;
			(*str)++;
		}
		result /= *power;
	}
	return (result);
}

double	ft_atof(t_scene *scene, char *str)
{
	double	result;
	double	sign;
	double	power;

	result = 0.0;
	sign = 1.0;
	power = 1.0;
	if (!ft_str_isfloat(str))
	{
		err("Incorrect float number");
		ft_exit(scene);
	}
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '-')
	{
		sign = -1.0;
		str++;
	}
	else if (*str == '+')
		str++;
	result = parse_integer_part(&str);
	result += parse_decimal_part(&str, &power);
	return (result * sign);
}
