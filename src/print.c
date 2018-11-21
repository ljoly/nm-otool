/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:29:53 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/21 18:40:17 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_syms(const t_bin bin)
{
	uint32_t	i;

	i = 0;
	while (i < bin.symtab->nsyms)
	{
		if (bin.syms[i].type == 'u' || bin.syms[i].type == 'U')
			printf("%18c %s\n", bin.syms[i].type, bin.syms[i].name);
		else if (bin.syms[i].type)
			printf("%.16llx %c %s\n", bin.syms[i].value, bin.syms[i].type,
				bin.syms[i].name);
		i++;
	}
}
