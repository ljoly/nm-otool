/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:12:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/14 15:28:07 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// static t_bool	is_dup(t_sym sym1, t_sym sym2)
// {
// 	return (ft_strequ(sym1.name, sym2.name) && sym1.value == sym2.value);
// }

void		sort_syms(t_sym *syms, uint32_t size)
{
	t_bool		sorted;
	uint32_t	i;
	int			cmp;
	t_sym		tmp;

	i = 0;
	sorted = FALSE;
	while (!sorted)
	{
		sorted = TRUE;
		i = 0;
		while (i < size - 1)
		{
			cmp = ft_strcmp(syms[i].name, syms[i + 1].name);
			if (cmp > 0)
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
				sorted = FALSE;
			}
			else if (cmp == 0 && syms[i].value > syms[i + 1].value)
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
				sorted = FALSE;
			}
			i++;
		}
	}
}
