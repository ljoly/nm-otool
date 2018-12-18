/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/18 19:16:56 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "flags.h"

int				main(int ac, char **av)
{
	int			fd;
	int			i;

	g_exit_status = EXIT_SUCCESS;
	if (!get_flags(ac, av))
	{
		return (g_exit_status);
	}
	if (ac < 2)
	{
		handle_arg("a.out", &fd);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (ac > 2)
				ft_printf("\n%s: \n", av[i]);
			handle_arg(av[i], &fd);
			close(fd);
			i++;
		}
	}
	return (g_exit_status);
}
