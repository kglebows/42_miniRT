/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:03:47 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:25:42 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Scales vector by scalar. Direction stays the same if scalar > 0.
 * if scalar < 0, vector direction will reverse.
 * if scalar == -1, the lenght remains the same and vector direction reverses.
 * @param vector vector to scale
 * @param scalar a value by which to scale the vector
 * @return vector scaled by scalar
 */
t_vector	v_scale(t_vector vector, double scalar)
{
	t_vector		new_vector;

	new_vector.x = vector.x * scalar;
	new_vector.y = vector.y * scalar;
	new_vector.z = vector.z * scalar;
	return (new_vector);
}

/**
 * @brief Adds two vectors. This operation is commutative.
 * @param vector1 first vector to add
 * @param vector2 second vector to add
 * @return result vector
 */
t_vector	v_add(t_vector vector1, t_vector vector2)
{
	t_vector		new_vector;

	new_vector.x = vector1.x + vector2.x;
	new_vector.y = vector1.y + vector2.y;
	new_vector.z = vector1.z + vector2.z;
	return (new_vector);
}

/**
 * @brief Subtracts vector2 from vector1. This operation is non-commutative.
 * @param vector1 The vector from which vector2 will be subtracted.
 * @param vector2 The vector to be subtracted from vector1.
 * @return The resulting vector after subtraction.
 */
t_vector	v_subtract(t_vector vector1, t_vector vector2)
{
	t_vector		new_vector;

	new_vector.x = vector1.x - vector2.x;
	new_vector.y = vector1.y - vector2.y;
	new_vector.z = vector1.z - vector2.z;
	return (new_vector);
}

/**
 * @brief Calculates the lenght of a vector.
 * Lenght of normalized vector is always == 1.
 * @param vector The vector to get lenght from.
 * @return The lenght of a vector.
 */
double	d_length(t_vector vector)
{
	double		lenght;

	lenght = sqrt(vector.x * vector.x + vector.y
			* vector.y + vector.z * vector.z);
	return (lenght);
}

/**
 * @brief Normalizes a vector so that its values are between -1 and 1.
 * Normalized vector has the same direction but its lenght == 1
 * @param vector The vector to normalize
 * @return The normalized vector
 */
t_vector	v_normalize(t_vector vector)
{
	t_vector	normalized;
	double		lenght;

	lenght = d_length(vector);
	normalized.x = vector.x / lenght;
	normalized.y = vector.y / lenght;
	normalized.z = vector.z / lenght;
	return (normalized);
}
