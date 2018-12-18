/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:43:33 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/18 19:17:28 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include "error.h"

static t_bool	is_flag(const char *f)
{
	return (ft_strequ(f, "-u") || ft_strequ(f, "-U") || ft_strequ(f, "-p") ||
		ft_strequ(f, "-j"), ft_strequ(f, "-g"));
}

t_bool			get_flags(int ac, char **av)
{
	int				i;
	static char		tab[5][2] = {"-u", "-U", "-p", "-j", "-g"};

	i = 0;
	g_flags = 0;
	while (i < ac && *av[i] == '-')
	{
		if (!is_flag(av[i]))
		{
			err_usage(FLAG, av[i]);
			return (FALSE);
		}

		i++;
	}
	return (TRUE);
}
