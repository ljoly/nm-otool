/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/21 19:17:01 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

int				main(int ac, char **av)
{
	int			fd;
	int			i;

	if (ac < 2)
	{
		err_cmd(ARG, NULL);
		return (EXIT_FAILURE);
	}
	g_exit_status = EXIT_SUCCESS;
	i = 1;
	while (i < ac)
	{
		if (ac > 2)
		{
			ft_printf("\n%s: \n", av[i]);
		}
		handle_arg(av[i], &fd);
		close(fd);
		i++;
	}
	return (g_exit_status);
}
