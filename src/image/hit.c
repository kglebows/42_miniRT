/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 11:30:06 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/16 13:28:48 by kglebows         ###   ########.fr       */
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
t_hit	ray_target_sphere(t_ray ray, t_elem *sp, t_dt *dt)
{
	t_hit		hit;
	t_qf		qf;

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
		hit.distance = d_closest_distance(qf);
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
t_hit	ray_target_plane(t_ray ray, t_elem *pl, t_dt *dt)
{
	t_hit		hit;
	double		denominator;

	denominator = d_dot(ray.d, pl->axis);
	hit.ray = ray;
	if (denominator < 1e-6)
		hit.type = BG;
	else
	{
		hit.type = PL;
		hit.color = pl->color;
		hit.distance = d_dot(v_scale(pl->oc, -1), pl->axis)
			/ denominator;
		hit.point = p_translate(
			v_scale(ray.d, hit.distance), ray.o);
		hit.norm = pl->axis;
	}
	return (hit);
}

t_hit	ray_hit_cylinder_side(t_hit hit, t_elem *cy, double m, t_dt *dt)
{
	t_hit	side;

	side.ray = hit.ray;
	side.distance = hit.distance;
	side.color = cy->color;
	side.type = CY;
	side.point = p_translate(v_scale(hit.ray.d, side.distance), hit.ray.o);
	side.norm = v_normalize(v_subtract(v_p2p(cy->center, side.point),
		v_scale(cy->axis, m)));
}

t_hit	ray_target_cylinder_caps(t_hit hit, t_elem *cy, t_dt *dt)
{
	t_hit	cap;

	
}

/**
 * @brief Checks if the ray hit the cylinder
 * @param ray ray that shoots towards the element
 * @param element element that is being checked for a hit
 * @param dt main data straucture
 * @attention In order to check if the ray intersects the cylinder
 * we have to use three equations:
 * 
 * P - hit point
 * A - point on cylinder axis with shortest distance to P
 * C - center of cylinder
 * h - height of cylinder
 * m - distance from C to A (max = h/2, min = -h/2)
 * O - ray origin (camera)
 * d - ray direction
 * t - distance from camera to hitpoint
 * n - axis of cylinder
 * r - radius of cylinder
 * 
 * A = C + n*m	where	(m >= -h/2 && m <= h/2)
 * (P<-A)⋅n = 0
 * len(P<-A) = r
 * 
 * after some mathemagic (ref) we get m :
 * 
 * m = d⋅n*t + (O<-C)⋅n
 * 
 * and for calculating t we end up with quadratic formula.
 * 
 * (-b +- sqr(b^2 - 4ac)) / 2a
 * 
 * where 
 * a = d⋅d - (d⋅n)*(d⋅n)
 * b = 2*(d⋅(O<-C) - (d⋅n)*((O<-C)⋅n))
 * c = (O<-C)⋅(O<-C) - ((O<-C)⋅n)*((O<-C)⋅n) - r*r
 * 
 * surface normal for sides is normalized vector (P<-A) = (P<-C) - n*m
 * and for the caps its n or -n depending on the cap
 * @ref https://shorturl.at/lDJ67
 * @return hit of cylinder type if hit or background type if no-hit
*/
t_hit	ray_target_cylinder(t_ray ray, t_elem *cy, t_dt *dt)
{
	t_hit		hit;
	t_qf		qf;
	double		m;

	qf = quadratic_formula(d_dot(ray.d, ray.d)
		- (d_dot(ray.d, cy->axis) * d_dot(ray.d, cy->axis)),
		2 * (d_dot(ray.d, cy->oc)
		- (d_dot(ray.d, cy->axis) * d_dot(cy->oc, cy->axis))),
		d_dot(cy->oc, cy->oc) 
		- (d_dot(cy->oc, cy->axis) * d_dot(cy->oc, cy->axis))
		- (cy->height / 2) * (cy->height / 2));
	hit.ray = ray;
	if (qf.discriminant >= 0)
	{
		hit.distance = d_shortest_distance(qf);
		m = d_dot(ray.d, cy->axis) * hit.distance + d_dot(cy->oc, cy->axis);
		if (m <= cy->height / 2 && m >= cy->height / -2)
			return (ray_hit_cylinder_side(hit, cy, m, dt));
	}
	return (ray_target_cylinder_caps(hit, cy, dt));
}
