/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:29:53 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 20:33:04 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "flags.h"

static void		print_syms32(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' && !is_no_undf() && !is_only_extern())
			ft_printf("%s\n", o.syms[i].name);
		else if (o.syms[i].type == 'U' && !is_no_undf())
			(is_only_names() || is_only_undf()) ?
				ft_printf("%s\n", o.syms[i].name) :
					ft_printf("%10c %s\n", o.syms[i].type, o.syms[i].name);
		else if (o.syms[i].type != 'U' && ft_isupper(o.syms[i].type)
			&& is_only_extern() && !is_only_undf())
			is_only_names() ? ft_printf("%s\n", o.syms[i].name) :
				ft_printf("%.8llx %c %s\n", o.syms[i].value,
					o.syms[i].type, o.syms[i].name);
		else if (o.syms[i].type != 'U' && o.syms[i].type &&
			!is_only_extern() && !is_only_undf())
			is_only_names() ? ft_printf("%s\n", o.syms[i].name) :
				ft_printf("%.8llx %c %s\n", o.syms[i].value, o.syms[i].type,
					o.syms[i].name);
		i++;
	}
}

static void		print_syms64(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' && !is_no_undf() && !is_only_extern())
			ft_printf("%s\n", o.syms[i].name);
		else if (o.syms[i].type == 'U' && !is_no_undf())
			(is_only_names() || is_only_undf()) ?
				ft_printf("%s\n", o.syms[i].name) :
					ft_printf("%18c %s\n", o.syms[i].type, o.syms[i].name);
		else if (o.syms[i].type != 'U' && ft_isupper(o.syms[i].type)
			&& is_only_extern() && !is_only_undf())
			is_only_names() ? ft_printf("%s\n", o.syms[i].name) :
				ft_printf("%.16llx %c %s\n", o.syms[i].value,
					o.syms[i].type, o.syms[i].name);
		else if (o.syms[i].type != 'U' && o.syms[i].type &&
			!is_only_extern() && !is_only_undf())
			is_only_names() ? ft_printf("%s\n", o.syms[i].name) :
				ft_printf("%.16llx %c %s\n", o.syms[i].value, o.syms[i].type,
					o.syms[i].name);
		i++;
	}
}

void			print_syms(const t_mach o, t_bool arch_64)
{
	if ((g_flags & 1) & ((g_flags >> 1) & 1))
		return ;
	if (arch_64)
	{
		print_syms64(o);
	}
	else
	{
		print_syms32(o);
	}
}
