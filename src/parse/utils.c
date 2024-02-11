/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:38:02 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/08 09:38:02 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void free_char_array(char **array) {
    if (array == NULL) return;

    int i = 0;
    while (array[i] != NULL) {
        free(array[i]);
        i++;
    }
    free(array);
}

size_t	ft_arraylen(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

t_point		gen_coord(double x, double y, double z)
{
	t_point	coord;

	coord.x = x;
	coord.y = y;
	coord.z = z;
	return (coord);
}
