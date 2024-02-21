/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_math.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 11:33:54 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/21 17:04:41 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_rgb	rgb_add(t_rgb base, t_rgb add)
{
	base.r = max(0, min(round(base.r + add.r), 255));
	base.g = max(0, min(round(base.g + add.g), 255));
	base.b = max(0, min(round(base.b + add.b), 255));
	return (base);
}

t_rgb	rgb_combine(t_rgb base, t_rgb combine, double ratio)
{
	ratio = max(0, min(ratio, 1)) / 255;
	base.r = max(0, min(round(base.r * combine.r * ratio), 255));
	base.g = max(0, min(round(base.g * combine.g * ratio), 255));
	base.b = max(0, min(round(base.b * combine.b * ratio), 255));
	return (base);
}

t_rgb	rgb_scale(t_rgb base, double ratio)
{
	ratio = max(0, min(ratio, 1)) / 255;
	base.r = max(0, min(round(base.r * ratio), 255));
	base.g = max(0, min(round(base.g * ratio), 255));
	base.b = max(0, min(round(base.b * ratio), 255));
	return (base);
}