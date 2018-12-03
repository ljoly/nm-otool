/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 13:56:16 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
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
	struct fat_header	*header;
	struct fat_arch		*arch;
	t_file				mach_o;
	int					magic;
	uint32_t			i;

	header = (struct fat_header *)f.ptr;
	if (!access_at(f, f.ptr + sizeof(*header)))
	{
		return (FALSE);
	}
	arch = f.ptr + sizeof(*header);
	i = 0;
	while (i < swap_32(header->nfat_arch, f.swap))
	{
		if (!access_at(f, (void*)arch + sizeof(*arch)))
			return (FALSE);
		if ((swap_32(arch->cputype, f.swap) == CPU_TYPE_X86_64))
		{
			if (!access_at(f, f.ptr + swap_32(arch->offset, f.swap)))
				return (FALSE);
			mach_o = get_mach_o_file(f.ptr, arch, f.swap);
			magic = *(int *)mach_o.ptr;
			handle_magic(magic, mach_o, arg);
			break ;
		}
		arch = (void*)arch + sizeof(*arch);
		i++;
	}
	return (TRUE);
}
