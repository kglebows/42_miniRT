/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kglebows <kglebows@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/25 12:21:45 by kglebows          #+#    #+#             */
/*   Updated: 2024/02/26 12:04:48 by kglebows         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief displays input string followed by a new line to
 * standard error
 * @param str string to be displayed (without \\n)
 * @return KO
*/
t_ok	err(char *str)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (KO);
}

/**
 * @brief displays input string followed by a new line to
 * standard output
 * @param str string to be displayed (without \\n)
 * @return OK
*/
t_ok	msg(char *str)
{
	ft_putstr_fd(str, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	return (OK);
}

/**
 * @brief If elements exist, frees the memory allocated for them.
 * @param dt main data structure
*/
void	free_elements(t_dt *dt)
{
	t_elem		*temp;

	if (dt && dt != NULL && dt->elements && dt->elements != NULL)
	{
		while (dt->elements != NULL)
		{
			temp = dt->elements->next;
			free(dt->elements);
			dt->elements = temp;
		}
		dt->elements = NULL;
	}
}

/**
 * @brief If ESCAPE key pressed, frees memory if needed and exits
*/
void	exit_esc(keys_t key, void *param)
{
	(void)param;
	if (key == MLX_KEY_ESCAPE)
	{
		exit(0);
	}
}

/**
 * @brief When called frees memory if needed and exits
*/
void	exit_win(void *param)
{
	t_dt		*dt;

	dt = param;
	free_elements(dt);
	exit(0);
}
