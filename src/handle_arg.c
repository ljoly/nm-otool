/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:58:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/27 17:59:27 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

static t_err	handle_file(const char *arg, int *fd, t_file *f)
{
	t_err		err;
	struct stat	buf;

	err = NO_ERR;
	if ((*fd = open(arg, O_RDONLY)) < 0)
	{
		err = OPEN;
	}
	if (fstat(*fd, &buf) < 0)
	{
		err = FSTAT;
	}
	if (S_ISDIR(buf.st_mode))
	{
		err = DIR;
	}
	if (!(f->size = buf.st_size))
	{
		err = FORMAT;
	}
	return (err);
}

void			handle_arg(const char *arg, int *fd)
{
	int			magic;
	t_file		f;
	t_err		err;

	if ((err = handle_file(arg, fd, &f)) != NO_ERR)
	{
		err_cmd(err, arg);
	}
	if ((f.ptr = mmap(0, f.size, PROT_READ, MAP_PRIVATE, *fd, 0))
		== MAP_FAILED)
	{
		err_cmd(MMAP, arg);
	}
	magic = *(int *)f.ptr;
	handle_magic(magic, f, arg);
	if (munmap(f.ptr, f.size) < 0)
	{
		err_cmd(MUNMAP, arg);
	}
}
