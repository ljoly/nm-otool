/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 21:21:34 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "flags.h"

int				main(int ac, char **av)
{
	int		n_arg;
	int		fd;
	int		i;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (!handle_flags(ac, av, &n_arg))
		return (EXIT_FAILURE);
	i = 1;
	while (i < ac)
	{
		if (*av[i] != '-')
		{
			if (n_arg > 1)
				ft_printf("\n%s: \n", av[i]);
			if (!handle_arg(av[i], &fd))
				exit_status = EXIT_FAILURE;
		}
		i++;
	}
	if (!n_arg)
		exit_status = (handle_arg("a.out", &fd) ? EXIT_SUCCESS : EXIT_FAILURE);
	close(fd);
	return (exit_status);
}
