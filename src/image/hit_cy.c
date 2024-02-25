/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_cy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:25:01 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:31:46 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	ray_hit_cylinder_side(t_hit hit, t_elem *cy, double m)
{
	t_hit	side;

	side.ray = hit.ray;
	side.distance = hit.distance;
	side.color = cy->color;
	side.type = CY;
	side.point = p_translate(v_scale(hit.ray.d, side.distance), hit.ray.o);
	side.norm = v_normalize(v_subtract(v_p2p(cy->center, side.point),
				v_scale(cy->axis, m)));
	return (side);
}

t_elem	cy_cap(t_elem *cy, int is_top)
{
	t_elem		cap;
	t_vector	trans;

	cap.color = cy->color;
	cap.type = PL;
	if (is_top != 0)
	{
		trans = v_scale(cy->axis, cy->height / 2);
		cap.axis = cy->axis;
	}
	else
	{
		trans = v_scale(cy->axis, cy->height / -2);
		cap.axis = v_scale(cy->axis, -1);
	}
	cap.center = p_translate(trans, cy->center);
	cap.oc = v_subtract(cy->oc, trans);
	cap.diameter = cy->diameter / 2;
	return (cap);
}

/**
 * @brief Checks if the ray hit the cap of cylinder
 * @param ray ray that shoots towards the element
 * @param element plane created from cylinder
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
 * Now on top of that we need to factor in the radius of cylinder.
 * To do so we need to solve:
 * (P<-C) * (P<-C) < radius * radius
 * we pass radius through diamater variable of the plane t_elem.
 * if this condition is not met, we throw BG
 * @ref https://mrl.cs.nyu.edu/~dzorin/rend05/lecture2.pdf
 * @return hit of plane type if hit or background type if no-hit
*/
t_hit	ray_target_cap(t_ray ray, t_elem pl)
{
	t_hit		hit;
	double		denominator;
	t_vector	hit_area;

	denominator = d_dot(v_normalize(ray.d), v_normalize(v_scale(pl.axis, -1)));
	hit.ray = ray;
	if (denominator < 1e-6 && denominator > -1e-6)
		hit.type = BG;
	else
	{
		hit.type = PL;
		hit.color = pl.color;
		hit.distance = d_dot(v_p2p(ray.o, pl.center), v_scale(pl.axis, -1))
			/ denominator;
		hit.point = p_translate(
				v_scale(v_normalize(ray.d), hit.distance), ray.o);
		hit.norm = pl.axis;
		hit_area = v_p2p(pl.center, hit.point);
		if (d_dot(hit_area, hit_area) >= pl.diameter * pl.diameter)
			hit.type = BG;
	}
	return (hit);
}

t_hit	ray_target_cylinder_caps(t_hit hit, t_elem *cy)
{
	t_hit		top;
	t_hit		bot;

	top = ray_target_cap(hit.ray, cy_cap(cy, 1));
	bot = ray_target_cap(hit.ray, cy_cap(cy, 0));
	if (top.type == BG && bot.type == BG)
		return (top);
	if (top.type == PL && bot.type == BG)
		return (top);
	if (top.type == BG && bot.type == PL)
		return (bot);
	if (top.distance < bot.distance)
		return (top);
	else
		return (bot);
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
t_hit	ray_target_cylinder(t_ray ray, t_elem *cy)
{
	t_hit		hit;
	t_qf		qf;
	double		m;

	cy->oc = v_p2p(cy->center, ray.o);
	qf = quadratic_formula(d_dot(ray.d, ray.d)
			- (d_dot(ray.d, cy->axis) * d_dot(ray.d, cy->axis)),
			2 * (d_dot(ray.d, cy->oc)
				- (d_dot(ray.d, cy->axis) * d_dot(cy->oc, cy->axis))),
			d_dot(cy->oc, cy->oc)
			- (d_dot(cy->oc, cy->axis) * d_dot(cy->oc, cy->axis))
			- (cy->diameter / 2) * (cy->diameter / 2));
	hit.ray = ray;
	if (qf.discriminant >= 0)
	{
		hit.distance = d_shortest_distance(qf);
		m = d_dot(ray.d, cy->axis) * hit.distance + d_dot(cy->oc, cy->axis);
		if (m <= cy->height / 2 && m >= cy->height / -2)
			return (ray_hit_cylinder_side(hit, cy, m));
	}
	return (ray_target_cylinder_caps(hit, cy));
}
