/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 18:43:09 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/24 17:03:28 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	char_validate(char *line, int *comma_count, int *valid_flag)
{
	size_t	i;

	i = 2;
	while (line[i])
	{
		if (!ft_strchr("0123456789,.- ", line[i]))
			*valid_flag = 1;
		if (line[i] == ',')
			*comma_count += 1;
		i++;
	}
}

void	validate(char *line, t_scene *scene)
{
	const char	*valid_chars;
	int			valid_flag;
	int			comma_count;

	valid_chars = "ALCspcy";
	valid_flag = 1;
	comma_count = 0;
	char_validate(line, &comma_count, &valid_flag);
	if (!ft_strchr(valid_chars, line[0]))
		valid_flag = 0;
	if ((line[0] == 'R' && comma_count != 0) || (line[0] == 'A'
			&& comma_count != 2) || ((line[0] == 'L' || (line[0] == 'C'
					&& line[1] == ' ') || (line[0] == 's' && line[1] == 'p'))
			&& comma_count != 4) || (((line[0] == 'p' && line[1] == 'l')
				|| (line[0] == 'c' && line[1] == 'y')) && comma_count != 6))
		valid_flag = 0;
	if (!valid_flag)
	{
		err("Invalid configuration");
		ft_exit(scene);
	}
}

void	scene_split_validation(t_scene *scene, int element_id)
{
	static size_t	element_attr_count[6];

	element_attr_count[0] = 3;
	element_attr_count[1] = 4;
	element_attr_count[2] = 4;
	element_attr_count[3] = 4;
	element_attr_count[4] = 4;
	element_attr_count[5] = 6;
	validate(scene->line, scene);
	scene->split = ft_split(scene->line, ' ');
	if (ft_arraylen(scene->split) != element_attr_count[element_id])
	{
		err("Invalid number of attributes");
		ft_exit(scene);
	}
}

int	line_check(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (len == 1 || *s == '#')
		return (1);
	if (len > 0 && s[len - 1] == '\n')
		s[len - 1] = '\0';
	return (0);
}
