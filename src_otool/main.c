/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:37:38 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/17 19:12:18 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int			main(int ac, char **av)
{
	int		i;
	int		fd;

	g_exit_status = EXIT_SUCCESS;
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
			handle_arg(av[i], &fd);
			close(fd);
			i++;
		}
	}
	return (g_exit_status);
}