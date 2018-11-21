/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:12:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/21 17:50:55 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void		sort_syms(t_sym *syms, uint32_t size)
{
	uint32_t	i;
	t_sym		tmp;

	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(syms[i].name, syms[i + 1].name) > 0)
		{
			tmp.value = syms[i].value;
			tmp.type = syms[i].type;
			tmp.name = syms[i].name;
			syms[i].value = syms[i + 1].value;
			syms[i].type = syms[i + 1].type;
			syms[i].name = syms[i + 1].name;
			syms[i + 1].value = tmp.value;
			syms[i + 1].type = tmp.type;
			syms[i + 1].name = tmp.name;
			i = -1;
		}
		i++;
	}
}
