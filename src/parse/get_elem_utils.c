/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_elem_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 09:58:54 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/07 09:58:54 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

bool	ft_strisint(char *str)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

bool	ft_str_isfloat(char *str)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(str))
	{
		if (!(ft_isdigit(str[i]) == true || str[i] == '-' || str[i] == '+'
				|| str[i] == '.'))
			return (false);
		i++;
	}
	return (true);
}

// double	ft_atof(const char *str)
// {
// 	double	int_part;
// 	double	dec_part;
// 	double	sign;
// 	int		i;

// 	int_part = 0.0;
// 	dec_part = 0.0;
// 	sign = 1.0;
// 	if (*str == '+' || *str == '-')
// 		if (*str++ == '-')
// 			sign = -1.0;
// 	while (ft_isdigit(*str))
// 		int_part = int_part * 10 + (*str++ - '0');
// 	i = -1;
// 	if (*str == '.' && *str++)
// 	{
// 		while (ft_isdigit(*str))
// 			dec_part += (pow(10, i--) * (*str++ - '0'));
// 	}
// 	return (sign * (int_part + dec_part));
// }
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

size_t	ft_arraylen(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}
