/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/06 16:22:52 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

int				main(int ac, char **av)
{
	t_env		e;
	int			fd;
	int			i;

    if (ac < 2)
    {
		err_usage(&e, ARG, NULL);
        return (EXIT_FAILURE);
    }
	i = 1;
	while (i < ac)
	{
		// debug only: print at the end of the program
		if (ac > 2)
		{
			ft_printf("\n%s: \n", av[i]);
		}
		//
		handle_arg(&e, av[i], &fd);
		close(fd);
		i++;
	}
    return (e.exit_status);
}
