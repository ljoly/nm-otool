/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:58:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 15:52:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

void			handle_arg(const char *arg, int *fd)
{
	struct stat	buf;

	if ((*fd = open(arg, O_RDONLY)) < 0)
	{
		err_sys(OPEN, arg);
		return ;
	}
	if (fstat(*fd, &buf) < 0)
	{
		err_sys(FSTAT, arg);
		return ;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err_usage(DIR, arg);
		return ;
	}
	if (!(g_size = buf.st_size))
	{
		err_usage(FORMAT, arg);
		return ;
	}
	if ((g_file = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, *fd, 0))
		== MAP_FAILED)
	{
		err_sys(MMAP, arg);
		return ;
	}
	handle_magic(arg);
	if (munmap(g_file, buf.st_size) < 0)
		err_sys(MUNMAP, arg);
}
