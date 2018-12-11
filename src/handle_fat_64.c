/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:04:04 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/11 15:50:08 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "fat.h"
#include "handle_memory.h"
#include "handle_magic.h"

static t_file	get_mach_o_file(void *file, struct fat_arch_64 *arch,
	t_bool swp)
{
	t_file		mach_o;

	mach_o.ptr = file + swp32(arch->offset, swp);
	mach_o.size = swp32(arch->size, swp);
	return (mach_o);
}

static void		init_data(t_file *f, t_fat_64 *fat)
{
	fat->header = (struct fat_header *)f->ptr;
	fat->arch = f->ptr + sizeof(*fat->header);
}

t_bool			handle_fat_64(t_file f, const char *arg)
{
	t_fat_64	fat;
	uint32_t	i;

	init_data(&f, &fat);
	if (!access_at(f, f.ptr + sizeof(*fat.header)))
		return (FALSE);
	i = 0;
	while (i < swp32(fat.header->nfat_arch, f.swp))
	{
		if (!access_at(f, (void*)fat.arch + sizeof(*fat.arch)))
			return (FALSE);
		if ((swp32(fat.arch->cputype, f.swp) == CPU_TYPE_X86_64))
		{
			if (!access_at(f, f.ptr + swp32(fat.arch->offset, f.swp)))
				return (FALSE);
			fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
			fat.magic = *(int *)fat.mach_o.ptr;
			handle_magic(fat.magic, fat.mach_o, arg);
			break ;
		}
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
		i++;
	}
	return (TRUE);
}
