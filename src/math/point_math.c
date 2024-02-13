/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:44:42 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/13 08:06:30 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Translates vector by changing its origin to point.
 * The result vector is a vector between point and vectors end.
 * @param vector The vector from which point will be subtracted.
 * @param point The point to be subtracted from vector.
 * @return The resulting vector with new start point and old end point.
 */
t_vector	v_translate(t_vector vector, t_point point)
{
	t_vector		new_vector;

	new_vector.x = vector.x - point.x;
	new_vector.y = vector.y - point.y;
	new_vector.z = vector.z - point.z;
	return (new_vector);
}

/**
 * @brief Translates point by vector.
 * @param vector The vector which will be added to point.
 * @param point The point to be translated by vector.
 * @return point translated by vector.
 */
t_point	p_translate(t_vector vector, t_point point)
{
	t_point		new_point;

	new_point.x = vector.x + point.x;
	new_point.y = vector.y + point.y;
	new_point.z = vector.z + point.z;
	return (new_point);
}

/**
 * @brief Creates vector between two points by substracting the start
 * point from the end point
 * @param start start point of a vector
 * @param end end point of a vector
 * @return The resulting vector between the two points in direction from
 * start point to end point
 */
t_vector	v_p2p(t_point start, t_point end)
{
	t_vector	vector;

	vector.x = end.x - start.x;
	vector.y = end.y - start.y;
	vector.z = end.z - start.z;
	return (vector);
}
