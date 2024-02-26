/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:38:02 by ekordi            #+#    #+#             */
/*   Updated: 2024/02/26 12:03:15 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

size_t	ft_arraylen(char **s)
{
	size_t	l;

	l = 0;
	while (s[l] != 0)
		l++;
	return (l);
}

t_elem	*t_elem_last(t_elem *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	t_elem_add_back(t_elem **lst, t_elem *new)
{
	t_elem	*last;

	last = t_elem_last(*lst);
	if (!last)
		*lst = new;
	else
		last->next = new;
}

int	check_file_type(const char *s)
{
	int			len;

	len = ft_strlen(s);
	
	if (len > 3 && s[len - 3] == '.' && s[len - 2] == 'r' && s[len - 1] == 't')
		return (0);
	else
	{
		err("Error: File is not of type '.rt'\n");
		return (1);
	}
}

int	ft_open(char *argv, t_scene *scene)
{
	int	fd;

	if (check_file_type(argv))
		ft_exit(scene);
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
		ft_exit(scene);
	}
	return (fd);
}
