/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:30:06 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:24:28 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Checks if the ray hit the sphere
 * @param ray ray that shoots towards the element
 * @param element element that is being checked for a hit
 * @param dt main data straucture
 * @attention In order to check if the ray intersects the sphere
 * we have to solve the formula
 * (x + sp.x)^2 + (y + sp.y)^2 + (z + sp.z)^2 = r^2
 * if C = (sp.x, sp.y, sp.z) and P = (x, y, z)
 * then we can use cross product of vector (P<-C) to fill the equation
 * (P<-C)⋅(P<-C) = r^2
 * then if we represent the P as O + td where d is ray direction,
 * O is ray origin and t is distance.
 * after some mathematical magic (ref) we end up with quadratic formula.
 * 
 * (-b +- sqr(b^2 - 4ac)) / 2a
 * 
 * where 
 * a = d⋅d
 * b = 2d⋅(O<-C)
 * c = (O<-C)⋅(O<-C) - r^2
 * @ref https://raytracing.github.io/books/RayTracingInOneWeekend.html
 * @return hit of sphere type if hit or background type if no-hit
*/
t_hit	ray_target_sphere(t_ray ray, t_elem *sp)
{
	t_hit		hit;
	t_qf		qf;

	sp->oc = v_p2p(sp->center, ray.o);
	qf = quadratic_formula(d_dot(ray.d, ray.d),
			2 * d_dot(ray.d, sp->oc),
			d_dot(sp->oc, sp->oc) - (sp->diameter / 2) * (sp->diameter / 2));
	hit.ray = ray;
	if (qf.discriminant < 0)
		hit.type = BG;
	else
	{
		hit.type = SP;
		hit.color = sp->color;
		hit.distance = d_shortest_distance(qf);
		hit.point = p_translate(
				v_scale(ray.d, hit.distance), ray.o);
		hit.norm = v_normalize(v_p2p(sp->center, hit.point));
	}
	return (hit);
}

/**
 * @brief Checks if the ray hit the plane
 * @param ray ray that shoots towards the element
 * @param element element that is being checked for a hit
 * @param dt main data straucture
 * @attention In order to check if the ray intersects the plane
 * we have to use the dot product of two perpendicular vectors (== 0).
 * First vector will be n - the normal of plane. The second we need to
 * create from hit point (P) and plane point (C). If the dot product == 0
 * then it means that the ray intersects the plane. the equation:
 * (P<-C)⋅n = 0
 * then if we represent the P as O + td where d is ray direction,
 * O is ray origin and t is distance.
 * now some mathematic magic (ref) and we get:
 * t = ((-(O<-C))⋅n)/(d⋅n)
 * so we got distance. Now we can use the denominator to determine hit.
 * If it gets close to 0, there is either no intersection or the ray perfectly
 * coincide giving infinite number of solutions. Either way, we throw BG.
 * @ref https://shorturl.at/abV56
 * @return hit of plane type if hit or background type if no-hit
*/
t_hit	ray_target_plane(t_ray ray, t_elem *pl)
{
	t_hit		hit;
	double		denominator;

	denominator = d_dot(v_normalize(v_scale(ray.d, 1)),
			v_normalize(v_scale(pl->axis, 1)));
	hit.ray = ray;
	if (denominator < 1e-6 && denominator > -1e-6)
		hit.type = BG;
	else
	{
		hit.type = PL;
		hit.color = pl->color;
		hit.distance = d_dot(v_p2p(pl->center, ray.o), v_scale(pl->axis, -1))
			/ denominator;
		hit.point = p_translate(
				v_scale(v_normalize(ray.d), hit.distance), ray.o);
		hit.norm = pl->axis;
		if (denominator >= 0)
			hit.norm = v_scale(pl->axis, -1);
	}
	return (hit);
}
