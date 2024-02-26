/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:21:41 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/26 12:04:51 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_exit(t_scene *scene)
{
	int		i;
	t_elem	*current;
	t_elem	*next;

	i = 0;
	current = scene->elements;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	scene->elements = NULL;
	if (scene->split != NULL)
		free_char_array(scene->split);
	exit(EXIT_FAILURE);
}
