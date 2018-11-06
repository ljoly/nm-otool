/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:18:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/05 17:40:14 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

static void		print_err(const char *err, const char *arg)
{
	ft_putstr_fd("Error: ", STDERR);
	ft_putstr_fd(arg, STDERR);
	ft_putstr_fd(": ", STDERR);
	ft_putendl_fd(err, STDERR);
}

void			err_sys(t_env *e, t_sys err_code, const char *arg)
{
	e->exit_status = EXIT_FAILURE;
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


void			err_usage(t_usage err_code)
{
	if (err_code == ARG)
	{
		ft_putendl_fd("Error: no argument provided", STDERR);
	}
    else if (err_code == MAGIC)
    {
        ft_putendl_fd("Error: wrong magic number", STDERR);
    }
}