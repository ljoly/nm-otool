/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:18:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 14:26:29 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

static void			print_err(const char *err, const char *arg)
{
	ft_putstr_fd("Error: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err, STDERR);
}

static void			err_sys(const t_err err_code, const char *arg)
{
	if (err_code == OPEN)
	{
		print_err("no such file or diretory", arg);
	}
	else if (err_code == FSTAT)
	{
		print_err("fstat", arg);
	}
	else if (err_code == MMAP)
	{
		print_err("mmap", arg);
	}
	else if (err_code == MUNMAP)
	{
		print_err("munmap", arg);
	}
}

static void			err_usage(const t_err err_code, const char *arg)
{
	if (err_code == FORMAT)
	{
		print_err("the file was not recognized as a valid object file", arg);
	}
	else if (err_code == DIR)
	{
		print_err("is a directory", arg);
	}
}

void				err_cmd(const t_err err, const char *arg)
{
	if (err == DIR || err == FORMAT)
	{
		err_usage(err, arg);
	}
	else if (err == OPEN || err == FSTAT || err == MMAP || err == MUNMAP
		|| err == MALLOC)
	{
		err_sys(err, arg);
	}
}
