/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_consistency.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:49:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/30 17:24:45 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** checking offsets
*/

t_bool		access_at(t_file f, const void *ptr)
{
	if (!(ptr - f.ptr >= 0 && ptr < f.ptr + f.size))
	{
		ft_printf("file = %u\nptr max = %u\nptr = %u\n", f.ptr, f.ptr + f.size, ptr);
	}
	return (ptr - f.ptr >= 0 && ptr < f.ptr + f.size);
}

/*
** checking the reliability of:
**   cmdsize
**   nsects
**   nsyms
*/

static t_bool		check_symtab(t_file f, t_bin *bin, t_bool bit64)
{
	struct nlist		*table;
	struct nlist_64		*table64;
	char				*strtable;
	uint32_t			nsyms;
	void				*ptr;

	table = f.ptr + bin->symtab->symoff;
	table64 = f.ptr + bin->symtab->symoff;
	strtable = f.ptr + bin->symtab->stroff;
	nsyms = bin->symtab->nsyms;
	if (bit64)
		ptr = (void*)table64 + nsyms * sizeof(*table64);
	else
		ptr = (void*)table + nsyms * sizeof(*table);
	if (!access_at(f, ptr))
		return (FALSE);
	if (bit64)
		ptr = strtable + table64[nsyms - 1].n_un.n_strx;
	else
		ptr = strtable + table[nsyms - 1].n_un.n_strx;
	if (!access_at(f, ptr))
		return (FALSE);
	return (TRUE);
}

static t_bool		check_sects(t_bin *bin, t_bool bit64)
{
	struct segment_command		*seg;
	struct segment_command_64	*seg64;

	seg = (struct segment_command*)bin->lc;
	seg64 = (struct segment_command_64*)bin->lc;
	if (bit64)
	{
		if (seg64->nsects * sizeof(struct section_64) + sizeof(*seg64)
			!= seg64->cmdsize)
		{
			return (FALSE);
		}
		bin->nsects += seg64->nsects;
	}
	else
	{
		if (seg->nsects * sizeof(struct section) + sizeof(*seg)
			!= seg->cmdsize)
		{
			return (FALSE);
		}
		bin->nsects += seg->nsects;
	}
	return (TRUE);
}

static t_bool		check_seg(t_file f, t_bin *bin, t_bool bit64)
{
	struct segment_command		*seg;
	struct segment_command_64	*seg64;

	seg = (struct segment_command*)bin->lc;
	seg64 = (struct segment_command_64*)bin->lc;
	if (bit64)
	{
		if (!(seg64->fileoff + seg64->filesize))
			return (TRUE);
		if (!access_at(f, f.ptr + seg64->fileoff + seg64->filesize - 1))
		{
			return (FALSE);
		}
	}
	else
	{
		if (!(seg->fileoff + seg->filesize))
			return (TRUE);
		if (!access_at(f, f.ptr + seg->fileoff + seg->filesize - 1))		
		{
			return (FALSE);
		}
	}
	return (TRUE);
}

t_bool		cmd_is_consistent(t_file f, t_bin *bin, t_bool bit64)
{
	if (!access_at(f, (void*)bin->lc + bin->lc->cmdsize))
	{
		return (FALSE);
	}
	if (bin->lc->cmd == LC_SEGMENT || bin->lc->cmd == LC_SEGMENT_64)
	{
		if (!check_seg(f, bin, bit64))
		{
			ft_putendl("SEG OFFSETS");
			return (FALSE);
		}
		if (!check_sects(bin, bit64))
		{
			ft_putendl("SECTS");
			return (FALSE);
		}
	}
	else if (bin->lc->cmd == LC_SYMTAB)
	{
		bin->symtab = (struct symtab_command *)bin->lc;
		if (!check_symtab(f, bin, bit64))
		{
			ft_putendl("SYMTAB");
			return (FALSE);
		}
	}
	return (TRUE);
}
