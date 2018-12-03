/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 13:43:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

static void		init_data(t_file *f, t_bin *bin)
{
	bin->header = (struct mach_header *)f->ptr;
	bin->lc = f->ptr + sizeof(struct mach_header_64);
	bin->symtab = NULL;
	bin->sects = NULL;
	bin->syms = NULL;
	bin->nsects = 0;
}

t_bool			handle_64(t_file f, const char *arg)
{
	t_bin		bin;
	uint32_t	sizeof_cmds;
	uint32_t	i;

	init_data(&f, &bin);
	if (!access_at(f, f.ptr + sizeof(struct mach_header_64)))
		return (FALSE);
	if (!bin.header->ncmds && !bin.header->sizeofcmds)
		return (TRUE);
	sizeof_cmds = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (!cmd64_is_consistent(f, &bin))
			return (FALSE);
		sizeof_cmds += bin.lc->cmdsize;
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	if (sizeof_cmds != bin.header->sizeofcmds || !get_sections_64(f, arg, &bin))
		return (FALSE);
	bin.lc = f.ptr + sizeof(struct mach_header_64);
	return (handle_syms(f, arg, &bin, &get_syms64));
}
