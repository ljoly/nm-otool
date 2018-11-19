/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 12:10:54 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void				handle_64(t_bool swap)
{
	t_bin						bin;
	uint32_t					i;

	if (swap)
	{
		ft_putendl("SWAP");
		return ;
	}
	bin.header = (struct mach_header *)g_file;
	bin.lc = g_file + sizeof(struct mach_header_64);
	bin.nsects = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (bin.lc->cmd == LC_SEGMENT_64)
		{
			count_sections_64(&bin);
		}
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	get_sections_64(&bin, g_file);
	i = 0;
	bin.lc = g_file + sizeof(struct mach_header_64);
	get_syms(bin, &print_sym64);
}
