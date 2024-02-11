/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors_operations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 10:44:49 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/11 10:44:49 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_point		v_add(t_point v, t_point u)
{
	return (gen_coord((v.x + u.x), (v.y + u.y), (v.z + u.z)));
}

t_point		v_sub(t_point v, t_point u)
{
	return (gen_coord((v.x - u.x), (v.y - u.y), (v.z - u.z)));
}

t_point		v_scale(t_point v, double f)
{
	return (gen_coord((f * v.x), (f * v.y), (f * v.z)));
}

t_point		v_cross(t_point v, t_point u)
{
	return (gen_coord(((v.y * u.z) - (v.z * u.y)),
						((v.z * u.x) - (v.x * u.z)),
						((v.x * u.y) - (v.y * u.x))));
}

double		v_dot(t_point v, t_point u)
{
	return ((v.x * u.x) + (v.y * u.y) + (v.z * u.z));
}
