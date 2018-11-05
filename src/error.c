/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:18:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/05 15:45:30 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

int		err_sys(t_sys err_code, const char *arg)
{
	if (err_code == OPEN)
	{
		ft_putstr_fd("Error: ", STDERR);
		ft_putstr_fd(arg, STDERR);
		ft_putendl_fd(" no such file or directory", STDERR);
	}
    return (EXIT_FAILURE);
}


int     err_usage(t_usage err_code)
{
    if (err_code == MAGIC)
    {
        ft_putendl_fd("Error: wrong magic number", STDERR);
    }
    return (EXIT_FAILURE);
}