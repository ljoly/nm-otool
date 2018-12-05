/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:29:53 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/05 12:32:26 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_syms(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' || o.syms[i].type == 'U')
		{
			ft_printf("%18c %s\n", o.syms[i].type, o.syms[i].name);
		}
		else if (o.syms[i].type)
		{
			ft_printf("%.16llx %c %s\n", o.syms[i].value, o.syms[i].type,
				o.syms[i].name);
		}
		i++;
	}
}
