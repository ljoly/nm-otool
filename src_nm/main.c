/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 19:01:47 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "flags.h"

int				main(int ac, char **av)
{
	int		n_arg;
	int		fd;
	int		i;

	g_exit_status = EXIT_SUCCESS;
	g_flags = 0;
	if (!handle_flags(ac, av, &n_arg))
		return (g_exit_status);
	i = 1;
	while (i < ac)
	{
		if (*av[i] != '-')
		{
			if (n_arg > 1)
				ft_printf("\n%s: \n", av[i]);
			handle_arg(av[i], &fd);
		}
		i++;
	}
	if (!n_arg)
	{
		handle_arg("a.out", &fd);
	}
	close(fd);
	return (g_exit_status);
}
