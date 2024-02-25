/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:20:07 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/25 12:36:34 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_scene	*initialize_scene(t_scene *scene)
{
	int	i;

	i = 0;
	scene = ft_calloc(sizeof(t_scene), 1);
	scene->line = NULL;
	scene->split = NULL;
	while (i < 9)
		scene->qtys[i++] = 0;
	scene->elements = NULL;
	return (scene);
}

int	main(int argc, char **argv)
{
	t_dt	dt;
	t_scene	*scene;

	scene = NULL;
	if (argc != 2)
		return (ft_putstr_fd("invalid nummber of aguments", 2), 1);
	scene = initialize_scene(scene);
	dt.scene = scene;
	pars_scene(argv[1], scene, &dt);
	if (render_mlx(&dt) == KO)
		exit_win(&dt);
	free_elements(&dt);
	mlx_loop(dt.mlx);
	return (0);
}
