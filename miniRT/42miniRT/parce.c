/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parce.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:25 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/28 15:13:08 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
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
void	get_resol(t_scene *scene, t_elem **new)
{
	scene->resol.x = get_posint(scene->split[1], "106");
	scene->resol.y = get_posint(scene->split[2], "106");
	if (new)
		return ;
}
void parse_element(int element_id, t_scene *scene)
{
	parse_function_arr function_arr[9] = {get_resol};
	t_elem *new;

	if(element_id > 2)
	{
	new = NULL;
	new = ft_calloc(sizeof(t_elem), 1);
	ft_bzero(new, 0);
	new->next = NULL;
	}
	//input validation must be implemented
	function_arr[element_id](scene, &new);
	scene->qtys[element_id]++;
}
void pars_scene(char *file, t_scene *scene)
{
	int fd = ft_open(file);
	static char	*s[9] = {"R ", "A ", "c ", "l ", "sp", "pl", "sq", "cy", "tr"};
	int element_id;

	while (scene->line = get_next_line(fd))
	{
		element_id = 0;
		while (s[element_id] && ft_strncmp(scene->line, s[element_id], 2))
			element_id++;
		if(element_id < 9)
			parse_element(element_id, scene);
		free(scene->line);
	}

}
