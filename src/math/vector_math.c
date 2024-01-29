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
 * @brief Calculates the lenght of a vector. Lenght of normalized vector is always == 1.
 * @param vector The vector to get lenght from.
 * @return The lenght of a vector.
 */
double	v_length(t_vector vector)
{
	double		lenght;

	lenght = 
}