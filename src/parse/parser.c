/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:25 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/22 19:22:17 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
int checkFileType(const char *filename) {
    const char *extension = ft_strrchr(filename, '.');
    if (extension != NULL && ft_strncmp(extension, ".rt", 3) == 0) {
        return 1;
    } else {
		ft_putstr_fd("Error: File is not of type '.rt'\n", 2);
        exit(EXIT_FAILURE);
    }
}

int	ft_open(char *argv)
{
	int	fd;
	checkFileType(argv);
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

void	validate(char *line)
{
	const char	*valid_chars;
	bool		valid_flag;
	size_t		i;
	int			comma_count;

	valid_chars = "RALCspcy";
	valid_flag = true;

	if (!ft_strchr(valid_chars, line[0]))
		valid_flag = false;
	i = 2;
	comma_count = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && !(line[i] == ',' || line[i] == '-'
			|| line[i] == ' ' || line[i] == '.'))
				valid_flag = false;
		if (line[i] == ',')
			comma_count++;
		i++;
	}

	if (line[0] == 'R' && comma_count != 0)
		valid_flag = false;
	if (line[0] == 'A' && comma_count != 2)
		valid_flag = false;
	if ((line[0] == 'L' || (line[0] == 'C' && line[1] == ' ') || (line[0] == 's' && line[1] == 'p'))
		&& comma_count != 4)
		valid_flag = false;
	if (((line[0] == 'p' && line[1] == 'l') || (line[0] == 'c' && line[1] == 'y')) && comma_count != 6)
		valid_flag = false;
	if (!valid_flag)
		{exit(EXIT_FAILURE);}
}
void	scene_split_validation(t_scene *scene, int element_id)
{
	static size_t	element_attr_count[7] = {3, 3, 4, 4, 4, 4, 6};
	int				i;

	i = 1;
	validate(scene->line);
	scene->split = ft_split(scene->line, ' ');
	if (ft_arraylen(scene->split) != element_attr_count[element_id])
		{ft_putstr_fd("Invalid number of attributes", 2);exit(EXIT_FAILURE);}
}

void	parse_element(int element_id, t_scene *scene)
{
	parse_function_arr	function_arr[7] = {get_resol, get_ambilight, get_camera, get_light, get_sp,
		get_pl, get_cy};

	scene_split_validation(scene, element_id);
			printf("hello motherfucker 2: return of motherfucker %d\n", element_id);
	function_arr[element_id](scene);
	scene->qtys[element_id]++;
	free_char_array(scene->split);
}
void	pars_scene(char *file, t_scene *scene)
{
	int				fd;
	static char		*s[7] = {"R ", "A ", "C ", "L ", "sp", "pl", "cy"};
	int				element_id;
	size_t			len;

	fd = ft_open(file);
	scene->line = get_next_line(fd);
	while (scene->line != NULL)
	{
		len = ft_strlen(scene->line);
		if (len > 0 && scene->line[len - 1] == '\n')
			scene->line[len - 1] = '\0';
		element_id = 0;
		while (s[element_id] && ft_strncmp(scene->line, s[element_id], 2))
			element_id++;
		if (element_id < 7)
		{
		printf("hello motherfucker : %s : %d \n", scene->line, element_id);
			parse_element(element_id, scene);
		}
		free(scene->line);
		scene->line = get_next_line(fd);
	}
	printf("hello motherfucker 3: freefuck\n");
}
