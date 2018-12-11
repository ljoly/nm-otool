/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/11 20:56:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "fat.h"
#include "handle_memory.h"
#include "handle_magic.h"

static t_file	get_mach_o_file(void *file, struct fat_arch *arch, t_bool swp)
{
	t_file		mach_o;

	mach_o.ptr = file + arch->offset;
	mach_o.size = swp32(&arch->size, swp);
	return (mach_o);
}

static t_bool	handle_ppc(t_file f, t_fat_32 fat, const char *arg)
{
	uint32_t	i;

	i = 0;
	fat.arch = f.ptr + sizeof(struct fat_header);
	while (i < fat.nfat_arch)
	{
		if (!access_at(f, f.ptr + swp32(&fat.arch->offset, f.swp)))
			return (FALSE);
		fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
		fat.magic = *(int *)fat.mach_o.ptr;
		handle_magic(fat.magic, fat.mach_o, arg);
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
		i++;
	}
	return (TRUE);
}

static void		init_data(t_file f, t_fat_32 *fat)
{
	fat->cpu_type_found = FALSE;
	fat->header = (struct fat_header *)f.ptr;
	fat->nfat_arch = swp32(&fat->header->nfat_arch, f.swp);
	fat->arch = f.ptr + sizeof(*fat->header);
}

t_bool			handle_fat_32(t_file f, const char *arg)
{
	t_fat_32	fat;
	uint32_t	i;

	init_data(f, &fat);
	if (!access_at(f, f.ptr + sizeof(*fat.header)))
		return (FALSE);
	i = 0;
	while (i < fat.nfat_arch)
	{
		if (!access_at(f, (void*)fat.arch + sizeof(*fat.arch)))
			return (FALSE);
		if ((swp_signed32(&fat.arch->cputype, f.swp) == CPU_TYPE_X86_64))
		{
			fat.cpu_type_found = TRUE;
			if (!access_at(f, f.ptr + swp32(&fat.arch->offset, f.swp)))
				return (FALSE);
			fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
			fat.magic = *(int *)fat.mach_o.ptr;
			handle_magic(fat.magic, fat.mach_o, arg);
			break ;
		}
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
		i++;
	}
	if (!fat.cpu_type_found)
		return (handle_ppc(f, fat, arg));
	return (TRUE);
}
