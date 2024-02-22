/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_product.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:04:45 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/13 07:30:53 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Dot product of two vectors. This operation is commutative. 
 * @param vector1 The vector to project the second vector on to.
 * @param vector2 The vector projected on first vector
 * @return if == 0 means the vectors are perpendicular (⟂).
 * if < 0 means the vectors have opposite directions.
 * for normalized vectors == 1 means the vectors are the same,
 * and == -1 means are in direct oposition.
 */
double	d_dot(t_vector vector1, t_vector vector2)
{
	double		dot;

	dot = vector1.x * vector2.x;
	dot += vector1.y * vector2.y;
	dot += vector1.z * vector2.z;
	return (dot);
}

/**
 * @brief Cross product of two vectors. This operation is non-commutative!
 * Cross product creates a third vector that is perpendicular to them both.
 * Its direction can be determined by using right hand rule :
 * @param vector1 first vector, its direction is your hand
 * @param vector2 second vector, its direction is your curved finger
 * @return vector perpendicular to both vectors, its direction is your thumb!
 * cross product creates a (0,0,0) vector if the vectors are parallel (∥)
 */
t_vector	v_cross(t_vector vector1, t_vector vector2)
{
	t_vector	new_vector;

	new_vector.x = vector1.y * vector2.z - vector1.z * vector2.y;
	new_vector.y = vector1.z * vector2.x - vector1.x * vector2.z;
	new_vector.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (new_vector);
}
