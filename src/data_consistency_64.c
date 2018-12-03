/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_consistency_64.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:49:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 14:08:45 by ljoly            ###   ########.fr       */
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

static t_bool		check_symtab(t_file f, t_mach *o)
{
	struct nlist_64		*table;
	char				*strtable;
	uint32_t			nsyms;
	void				*ptr;

	table = f.ptr + o->symtab->symoff;
	strtable = f.ptr + o->symtab->stroff;
	nsyms = o->symtab->nsyms;
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

static t_bool		check_sects(t_mach *o)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)o->lc;
	if (seg->nsects * sizeof(struct section_64) + sizeof(*seg)
		!= seg->cmdsize)
	{
		return (FALSE);
	}
	o->nsects += seg->nsects;
	return (TRUE);
}

static t_bool		check_seg(t_file f, t_mach *o)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)o->lc;
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

t_bool		cmd64_is_consistent(t_file f, t_mach *o)
{
	if (!access_at(f, (void*)o->lc + o->lc->cmdsize))
	{
		return (FALSE);
	}
	if (o->lc->cmd == LC_SEGMENT_64)
	{
		if (!check_seg(f, o))
		{
			ft_putendl("SEG OFFSETS");
			return (FALSE);
		}
		if (!check_sects(o))
		{
			ft_putendl("SECTS");
			return (FALSE);
		}
	}
	else if (o->lc->cmd == LC_SYMTAB)
	{
		o->symtab = (struct symtab_command *)o->lc;
		if (!check_symtab(f, o))
		{
			ft_putendl("SYMTAB");
			return (FALSE);
		}
	}
	return (TRUE);
}
