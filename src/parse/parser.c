/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:25 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/26 11:55:54 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	replace_tabs_with_spaces(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}

void	parse_element(int element_id, t_scene *scene, t_dt *dt)
{
	t_parse_function_arr	function_arr[6];

	function_arr[0] = get_ambilight;
	function_arr[1] = get_camera;
	function_arr[2] = get_light;
	function_arr[3] = get_sp;
	function_arr[4] = get_pl;
	function_arr[5] = get_cy;
	scene_split_validation(scene, element_id);
	function_arr[element_id](scene, dt);
	scene->qtys[element_id]++;
}

void	quantity_check(t_scene *scene)
{
	if (scene->qtys[0] > 1 || scene->qtys[1] != 1 || scene->qtys[2] > 1)
	{
		err("Invalid quantity of Ambilight || Camera || Light");
		ft_exit(scene);
	}
}

void	pars_scene(char *file, t_scene *scene, t_dt *dt)
{
	int		fd;
	int		element_id;
	char	**elements_split;

	elements_split = ft_split("A C L sp pl cy", ' ');
	fd = ft_open(file, scene);
	while (42)
	{
		free(scene->line);
		scene->line = get_next_line(fd);
		if (!scene->line)
			break ;
		replace_tabs_with_spaces(scene->line);
		if (line_check(scene->line))
			continue ;
		element_id = 0;
		while (elements_split[element_id] && ft_strncmp(scene->line,
				elements_split[element_id], 1))
			element_id++;
		if (element_id < 6)
			parse_element(element_id, scene, dt);
		free_char_array(scene->split);
	}
	quantity_check(scene);
	free_char_array(elements_split);
} 
