/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekordi <ekordi@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/14 17:34:21 by apuchill          #+#    #+#             */
/*   Updated: 2024/01/27 16:52:15 by ekordi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void		*malloc_ver(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (ptr == NULL)
		error_msg_and_exit(SYSERR);
	return (ptr);
}

int			open_ver(char *file)
{
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error_msg_and_exit(SYSERR);
	return (fd);
}

void		close_ver(int fd)
{
	if (close(fd) < 0)
		error_msg_and_exit(SYSERR);
}
