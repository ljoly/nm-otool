/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 18:43:33 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 19:13:59 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include "error.h"

static t_flag	g_tab[6] = {
	{"-u", ONLY_UNDF},
	{"-U", NO_UNDF},
	{"-j", ONLY_NAMES},
	{"-p", NO_SORT},
	{"-g", ONLY_EXTERN},
};

static t_bool	is_dup(int bit)
{
	return (((g_flags >> bit) & 1));
}

static t_flag	get_flag(const char *arg)
{
	unsigned long	i;
	unsigned long	len;
	t_flag			flag;

	i = 0;
	flag.name = NULL;
	flag.code = 0;
	len = sizeof(g_tab) / sizeof(*g_tab);
	while (i < len)
	{
		if (ft_strequ(arg, g_tab[i].name))
		{
			if (is_dup(i))
				flag.code = -1;
			else
			{
				g_flags = g_flags | g_tab[i].code;
				flag = g_tab[i];
			}
			break ;
		}
		i++;
	}
	return (flag);
}

t_bool			handle_flags(int ac, char **av, int *n_arg)
{
	int			i;
	t_flag		flag;

	i = 1;
	*n_arg = 0;
	while (i < ac)
	{
		if (*av[i] == '-')
		{
			flag = get_flag(av[i]);
			if (!flag.code || flag.code == -1)
			{
				!flag.code ?
					err_cmd(NOT_A_FLAG, av[i]) : err_cmd(FLAG_DUP, av[i]);
				return (FALSE);
			}
		}
		else
			*n_arg += 1;
		i++;
	}
	return (TRUE);
}
