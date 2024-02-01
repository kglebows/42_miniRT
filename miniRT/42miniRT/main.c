/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:42:09 by ekordi            #+#    #+#             */
/*   Updated: 2024/01/28 12:29:57 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return(ft_putstr_fd("invalid nummber of aguments", 2), 1);
	t_scene scene;
	pars_scene(argv[1], &scene)



	return 0;


}
