/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:58:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/06 16:23:05 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

void			handle_arg(t_env *e, char *arg, int *fd)
{
	struct stat	buf;

	if ((*fd = open(arg, O_RDONLY)) < 0)
	{
		err_sys(e, OPEN, arg);
		return ;
	}
	if (fstat(*fd, &buf) < 0)
	{
		err_sys(e, FSTAT, arg);
		return ;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err_usage(e, DIR, arg);
		return;
	}
	if ((e->p = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, *fd, 0))
		== MAP_FAILED)
	{
		err_sys(e, MMAP, arg);
		return ;
	}
	if (!handle_magic(e->p))
	{
		err_usage(e, MAGIC, arg);
	}
	if (munmap(e->p, buf.st_size) < 0)
	{
		err_sys(e, MUNMAP, arg);
		return ;
	}
}
