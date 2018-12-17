/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:12:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/17 17:23:35 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		swap_syms(t_sym *sym1, t_sym *sym2)
{
	t_sym		tmp;

	tmp.value = sym1->value;
	tmp.type = sym1->type;
	tmp.name = sym1->name;
	sym1->value = sym2->value;
	sym1->type = sym2->type;
	sym1->name = sym2->name;
	sym2->value = tmp.value;
	sym2->type = tmp.type;
	sym2->name = tmp.name;
}

void			sort_syms(t_sym *syms, uint32_t size)
{
	t_bool		sorted;
	uint32_t	i;
	int			cmp;

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
				swap_syms(&syms[i], &syms[i + 1]);
				sorted = FALSE;
			}
			else if (cmp == 0 && syms[i].value > syms[i + 1].value)
			{
				swap_syms(&syms[i], &syms[i + 1]);
				sorted = FALSE;
			}
			i++;
		}
	}
}
