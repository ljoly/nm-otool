/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/26 18:33:26 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

static void		swap64(void)
{
	ft_putendl("SWAP64");
	exit(0);
}

static void		init_data(t_bin *bin)
{
	bin->header = (struct mach_header *)g_file;
	bin->lc = g_file + sizeof(struct mach_header_64);
	bin->sects = NULL;
	bin->syms = NULL;
	bin->nsects = 0;
}

t_bool			handle_64(t_bool swap)
{
	t_bin		bin;
	uint32_t	sizeof_cmds;
	uint32_t	i;

	if (swap)
		swap64();
	init_data(&bin);
	if (!access_at(g_file + sizeof(struct mach_header_64)))
		return (FALSE);
	if (!bin.header->ncmds && !bin.header->sizeofcmds)
		return (TRUE);
	sizeof_cmds = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (!cmd_is_consistent(&bin, LC_SEGMENT_64, &check_sects_64))
			return (FALSE);
		sizeof_cmds += bin.lc->cmdsize;
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	if (sizeof_cmds != bin.header->sizeofcmds || !get_sections_64(&bin))
		return (FALSE);
	bin.lc = g_file + sizeof(struct mach_header_64);
	return (handle_syms(&bin, &get_syms64));
}
