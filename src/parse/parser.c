/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:25 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/07 16:10:27 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	ft_open(char *argv)
{
	int	fd;

	fd = open(argv, O_RDONLY);
	if (fd == -1)
	{
		if (errno == EACCES)
			ft_putstr_fd("zsh: permission denied: ", 2);
		else if (errno == ENOENT)
			ft_putstr_fd("zsh: no such file or directory: ", 2);
		else
			ft_putstr_fd("zsh: error opening the file: ", 2);
		ft_putstr_fd(argv, 2);
		ft_putstr_fd("\n", 2);
	}
	return (fd);
}

bool	ftstrisint(char *str)
{
	int	i;

	i = 0;
	while (i <= ft_strlen(str))
	{
		if (!ft_isdigit(str[i++]))
			return (false);
	}
	return (true);
}

void	scene_split_validation(t_scene *scene, int element_id)
{
	static int element_attr_count[9] = {3, 3, 4, 4, 4, 4, 5, 6, 5};
	int i = 1;

	while (scene->line[i])
	{
		if (!ft_isalnum(scene->line[i]) && (scene->line[i] != ',' ||
				scene->line[i] != ' ' || scene->line[i] != '-'))
			exit(5);
		i++;
	}
	scene->split = ft_split(scene->line, ' ');
	if (ft_arraylen(scene->split) != element_attr_count[element_id])
		exit(6);
}

void	parse_element(int element_id, t_scene *scene)
{
	parse_function_arr	function_arr[9] = {get_resol, get_ambilight, get_camera, get_light};
	t_elem				*new;

	if (element_id > 2)
	{
		new = NULL;
		new = ft_calloc(sizeof(t_elem), 1);
		ft_bzero(new, 0);
		new->next = NULL;
	}
	scene_split_validation(scene, element_id);
	function_arr[element_id](scene, &new);
	scene->qtys[element_id]++;
	free_char_array(scene->split);
}
void	pars_scene(char *file, t_scene *scene)
{
	int			fd;
	static char	*s[9] = {"R ", "A ", "c ", "l ", "sp", "pl", "sq", "cy", "tr"};
	int			element_id;

	fd = ft_open(file);
	scene->line = get_next_line(fd);
	while (scene->line != NULL)
	{
		element_id = 0;
		while (s[element_id] && ft_strncmp(scene->line, s[element_id], 2))
			element_id++;
		if (element_id < 9)
			parse_element(element_id, scene);
		free(scene->line);
		scene->line = get_next_line(fd);
	}
}
