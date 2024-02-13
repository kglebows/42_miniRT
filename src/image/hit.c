/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:30:06 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/13 12:32:08 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

closest_distance(double discriminant, double a, double b)
{
	double dist1;
	double dist2;

	if (discriminant == 0)
		return ((-1 * b) / (2 * a))
	dist1 = ((-1 * b) - sqrt(discriminant)) / (2 * a);
	dist2 = ((-1 * b) + sqrt(discriminant)) / (2 * a);
	if (dist1 < dist2)
		return (dist1);
	else
		return (dist2);
}

/**
 * @brief Checks if the ray hit the sphere
 * @param ray ray that shoots towards the element
 * @param element element that is being checked for a hit
 * @param dt main data straucture
 * @attention In order to check if the ray intersects the sphere
 * we have to solve the formula
 * (x + sp.x)^2 + (y + sp.y)^2 + (z + sp.z)^2 = r^2
 * if C = (sp.x, sp.y, sp.z) and P = (x, y, z)
 * then we can use cross product of vector (P - C) to fill the equation
 * (P - C)⋅(P - C) = r^2
 * then if we represent the P as A + td where d is ray direction,
 * A is ray origin and t is distance.
 * after some mathematical magic (ref) we end up with quadratic formula.
 * >>(-b +- sqr(b^2 - 4ac)) / 2a<<
 * where 
 * a = d⋅d
 * b = 2d⋅(A - C)
 * c = (A - C)⋅(A - C) - r^2
 * @ref https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * @return hit of sphere type if hit or background type if no-hit
*/
t_hit	ray_target_sphere(t_ray ray, t_elem *element, t_dt *dt)
{
	t_hit		hit;
	double		a;
	double		b;
	double		c;
	double		discriminant;

	a = d_dot(ray.direction, ray.direction);
	b = 2 * d_dot(ray.direction, v_p2p(ray.origin, element->center));
	c = d_dot(v_p2p(ray.origin, element->center)
		,v_p2p(ray.origin, element->center))
		- (element->diameter / 2) * (element->diameter / 2);
	discriminant = b * b - (4 * a * c);
	hit.ray = ray;
	if (discriminant < 0)
		hit.type = BG;
	else
	{
		hit.type = SP;
		hit.color = element->color;
		hit.distance = closest_distance(discriminant, a, b);
		hit.point = p_translate(
			v_scale(ray.direction, hit.distance), ray.origin);
		hit.norm = v_normalize(v_p2p(element->center, hit.point));
	}
	return (hit);
}

t_hit	ray_target_plane(t_ray ray, t_elem *element, t_dt *dt)
{
	
}

t_hit	ray_target_cylinder(t_ray ray, t_elem *element, t_dt *dt)
{

}