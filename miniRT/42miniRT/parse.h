/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:40 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/28 15:11:59 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <limits.h>
# include <errno.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <termios.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft/libft.h"

typedef void		(*parse_function_arr)(t_scene *, t_elem **);

typedef struct		s_coord
{
	double			x;
	double			y;
	double			z;
}					t_coord;

typedef struct		s_resol
{
	int				x;
	int				y;
}					t_resol;

typedef struct		s_scene
{
	char			*line;
	char			**split;
	short int		qtys[9];
	t_resol			resol;
}					t_scene;

typedef struct		s_elem
{
	t_coord			point;
	t_coord			normal;
	t_coord			*vertex;
	short int		qtd_vertex;
	int				colour;
	double			ratio;
	double			diam;
	double			height;
	struct s_elem	*next;
}					t_elem;
#endif
