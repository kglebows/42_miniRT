/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 15:44:42 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:25:55 by kglebows         ###   ########.fr       */
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

/**
 * @brief creates a quadratic formula structure and calculates discriminant.
 * Quadratic formula : 
 * a*x^2 + b*x + c = 0
 * @param a a factor
 * @param b b factor
 * @param c c factor
 * @attention Quadratic formula is used to find x. Depending on the value 
 * of discriminant there are no solutions (discriminant < 0), there is one
 * solution (disctiminant = 0), or there are two solutions (discriminant > 0)
 * The x formula is :
 * x = (-b +- sqr(b^2 - 4ac)) / 2a
 * discriminant = (b^2 - 4ac)
 * @return quadratic formula structure containing a, b, c and discriminant
 */
t_qf	quadratic_formula(double a, double b, double c)
{
	t_qf	qf;

	qf.a = a;
	qf.b = b;
	qf.c = c;
	qf.discriminant = b * b - (4 * a * c);
	return (qf);
}

/**
 * @brief returns the shortest distance through solving the quadratic formula
 * @param qf a, b, c and discriminant required to calculate x
 * @attention Quadratic formula is used to find x. Depending on the value 
 * of discriminant there are no solutions (discriminant < 0), there is one
 * solution (disctiminant = 0), or there are two solutions (discriminant > 0)
 * The x formula is :
 * x = (-b +- sqr(b^2 - 4ac)) / 2a
 * discriminant = (b^2 - 4ac)
 * @return shortest distance (smallest x)
 */
double	d_shortest_distance(t_qf qf)
{
	double		dist1;
	double		dist2;

	if (qf.discriminant == 0)
		return ((-1 * qf.b) / (2 * qf.a));
	dist1 = ((-1 * qf.b) - sqrt(qf.discriminant)) / (2 * qf.a);
	dist2 = ((-1 * qf.b) + sqrt(qf.discriminant)) / (2 * qf.a);
	if (dist1 < dist2)
		return (dist1);
	else
		return (dist2);
}
