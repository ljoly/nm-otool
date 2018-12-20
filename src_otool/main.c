/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 15:33:27 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			main(int ac, char **av)
{
	int		i;
	int		fd;
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	if (ac < 2)
	{
		ft_putendl_fd("Error: at least one file must be specified", STDERR);
		return (EXIT_FAILURE);
	}
	else
	{
		i = 1;
		while (i < ac)
		{
			if (!handle_arg(av[i], &fd))
				exit_status = EXIT_FAILURE;
			close(fd);
			i++;
		}
	}
	return (exit_status);
}
