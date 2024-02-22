/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:38:02 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/18 14:42:30 by ekordi           ###   ########.fr       */
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

t_elem	*t_elem_last(t_elem *lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
t_cam	*t_cam_last(t_cam *lst)
{
	if (!lst)
		return (0);
	while (lst -> next)
		lst = lst -> next;
	return (lst);
}
void	t_elem_add_back(t_elem **lst, t_elem *new)
{
	t_elem	*last;

	last = t_elem_last(*lst);
	if (!last)
		*lst = new;
	else
		last -> next = new;
}
void	t_cam_add_back(t_cam **lst, t_cam *new)
{
	t_cam	*last;

	last = t_cam_last(*lst);
	if (!last)
		*lst = new;
	else
		last -> next = new;
}
