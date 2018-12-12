/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_consistency_32.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:13:01 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 18:05:14 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

/*
** checking 32-bit arch offsets:
*/

static t_bool		check_symtab(t_file f, t_mach *o)
{
	struct nlist		*table;
	char				*strtable;
	uint32_t			nsyms;
	void				*ptr;
	uint32_t			i;

	table = f.ptr + swp32(&o->symtab->symoff, f.swp);
	strtable = f.ptr + swp32(&o->symtab->stroff, f.swp);
	nsyms = swp32(&o->symtab->nsyms, f.swp);
	ptr = (void*)table + nsyms * sizeof(*table);
	i = 0;
	while (i < nsyms)
	{
		if (!access_at(f, ptr))
		{
			return (FALSE);
		}
		ptr = strtable + swp32(&table[i].n_un.n_strx, f.swp);
		i++;
	}
	return (TRUE);
}

static t_bool		check_sects(t_file f, t_mach *o)
{
	struct segment_command		*seg;

	seg = (struct segment_command*)o->lc;
	if (swp32(&seg->nsects, f.swp) * sizeof(struct section) + sizeof(*seg)
		!= seg->cmdsize)
	{
		return (FALSE);
	}
	o->nsects += seg->nsects;
	return (TRUE);
}

static t_bool		check_seg(t_file f, t_mach *o)
{
	struct segment_command		*seg;

	seg = (struct segment_command*)o->lc;
	if (!(swp32(&seg->fileoff, f.swp) + swp32(&seg->filesize, f.swp)))
	{
		return (TRUE);
	}
	if (!access_at(f, f.ptr + seg->fileoff + seg->filesize - 1))
	{
		return (FALSE);
	}
	return (TRUE);
}

t_bool				cmd32_is_consistent(t_file f, t_mach *o)
{
	if (!access_at(f, (void*)o->lc + swp32(&o->lc->cmdsize, f.swp)))
	{
		return (FALSE);
	}
	if (swp32(&o->lc->cmd, f.swp) == LC_SEGMENT)
	{
		if (!check_seg(f, o))
		{
			ft_putendl("SEG OFFSETS");
			return (FALSE);
		}
		if (!check_sects(f, o))
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
