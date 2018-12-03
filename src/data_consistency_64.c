/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_consistency_64.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:49:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 13:42:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

/*
** checking the reliability of:
**   cmdsize
**   nsects
**   nsyms
*/

static t_bool		check_symtab(t_file f, t_bin *bin)
{
	struct nlist_64		*table;
	char				*strtable;
	uint32_t			nsyms;
	void				*ptr;

	table = f.ptr + bin->symtab->symoff;
	strtable = f.ptr + bin->symtab->stroff;
	nsyms = bin->symtab->nsyms;
	ptr = (void*)table + nsyms * sizeof(*table);
	if (!access_at(f, ptr))
	{
		return (FALSE);
	}
	ptr = strtable + table[nsyms - 1].n_un.n_strx;
	if (!access_at(f, ptr))
	{
		return (FALSE);
	}
	return (TRUE);
}

static t_bool		check_sects(t_bin *bin)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)bin->lc;
	if (seg->nsects * sizeof(struct section_64) + sizeof(*seg)
		!= seg->cmdsize)
	{
		return (FALSE);
	}
	bin->nsects += seg->nsects;
	return (TRUE);
}

static t_bool		check_seg(t_file f, t_bin *bin)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)bin->lc;
	if (!(seg->fileoff + seg->filesize))
	{
		return (TRUE);
	}
	if (!access_at(f, f.ptr + seg->fileoff + seg->filesize - 1))
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool		cmd64_is_consistent(t_file f, t_bin *bin)
{
	if (!access_at(f, (void*)bin->lc + bin->lc->cmdsize))
	{
		return (FALSE);
	}
	if (bin->lc->cmd == LC_SEGMENT_64)
	{
		if (!check_seg(f, bin))
		{
			ft_putendl("SEG OFFSETS");
			return (FALSE);
		}
		if (!check_sects(bin))
		{
			ft_putendl("SECTS");
			return (FALSE);
		}
	}
	else if (bin->lc->cmd == LC_SYMTAB)
	{
		bin->symtab = (struct symtab_command *)bin->lc;
		if (!check_symtab(f, bin))
		{
			ft_putendl("SYMTAB");
			return (FALSE);
		}
	}
	return (TRUE);
}
