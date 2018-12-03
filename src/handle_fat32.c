/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 14:27:40 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "fat.h"
#include "handle_memory.h"
#include "handle_magic.h"

static t_file	get_mach_o_file(void *file, struct fat_arch *arch, t_bool swap)
{
	t_file		mach_o;

	mach_o.ptr = file + swap_32(arch->offset, swap);
	mach_o.size = swap_32(arch->size, swap);
	return (mach_o);
}

t_bool			handle_fat32(t_file f, const char *arg)
{
	t_fat		fat;
	uint32_t	i;

	fat.header = (struct fat_header *)f.ptr;
	if (!access_at(f, f.ptr + sizeof(*fat.header)))
		return (FALSE);
	fat.arch = f.ptr + sizeof(*fat.header);
	i = 0;
	while (i < swap_32(fat.header->nfat_arch, f.swap))
	{
		if (!access_at(f, (void*)fat.arch + sizeof(*fat.arch)))
			return (FALSE);
		if ((swap_32(fat.arch->cputype, f.swap) == CPU_TYPE_X86_64))
		{
			if (!access_at(f, f.ptr + swap_32(fat.arch->offset, f.swap)))
				return (FALSE);
			fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swap);
			fat.magic = *(int *)fat.mach_o.ptr;
			handle_magic(fat.magic, fat.mach_o, arg);
			break ;
		}
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
		i++;
	}
	return (TRUE);
}
