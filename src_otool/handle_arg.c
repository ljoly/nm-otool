/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:58:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 15:58:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

static t_err	handle_file(const char *arg, int *fd, t_file *f)
{
	struct stat	buf;

	if ((*fd = open(arg, O_RDONLY)) < 0)
	{
		return (OPEN);
	}
	else if (fstat(*fd, &buf) < 0)
	{
		return (FSTAT);
	}
	else if (S_ISDIR(buf.st_mode))
	{
		return (DIR);
	}
	else if (!(f->size = buf.st_size))
	{
		return (FORMAT);
	}
	return (NO_ERR);
}

t_bool			handle_arg(const char *arg, int *fd)
{
	int			magic;
	t_file		f;
	t_err		err;

	if ((err = handle_file(arg, fd, &f)) != NO_ERR)
	{
		err_cmd(err, arg);
		return (FALSE);
	}
	if ((f.ptr = mmap(0, f.size, PROT_READ | PROT_WRITE, MAP_PRIVATE, *fd, 0))
		== MAP_FAILED)
	{
		err_cmd(MMAP, arg);
		return (FALSE);
	}
	magic = *(int *)f.ptr;
	if (!handle_magic_otool(magic, f, arg, TRUE))
		return (FALSE);
	if (munmap(f.ptr, f.size) < 0)
	{
		err_cmd(MUNMAP, arg);
		return (FALSE);
	}
	return (TRUE);
}
