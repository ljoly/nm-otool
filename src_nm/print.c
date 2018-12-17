/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:29:53 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/17 22:28:04 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		print_syms32(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' || o.syms[i].type == 'U')
		{
			ft_printf("%10c %s\n", o.syms[i].type, o.syms[i].name);
		}
		else if (o.syms[i].type == 'i' || o.syms[i].type == 'I')
		{
			ft_printf("%10c %s (indirect for %s)\n", o.syms[i].type,
				o.syms[i].name, o.syms[i].name);
		}
		else if (o.syms[i].type)
		{
			ft_printf("%.8llx %c %s\n", o.syms[i].value, o.syms[i].type,
				o.syms[i].name);
		}
		i++;
	}
}

static void		print_syms64(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' || o.syms[i].type == 'U')
		{
			ft_printf("%18c %s\n", o.syms[i].type, o.syms[i].name);
		}
		else if (o.syms[i].type == 'i' || o.syms[i].type == 'I')
		{
			ft_printf("%18c %s (indirect for %s)\n", o.syms[i].type,
				o.syms[i].name, o.syms[i].name);
		}
		else if (o.syms[i].type)
		{
			ft_printf("%.16llx %c %s\n", o.syms[i].value, o.syms[i].type,
				o.syms[i].name);
		}
		i++;
	}
}

void			print_syms(const t_mach o, t_bool arch_64)
{
	if (arch_64)
	{
		print_syms64(o);
	}
	else
	{
		print_syms32(o);
	}
}
