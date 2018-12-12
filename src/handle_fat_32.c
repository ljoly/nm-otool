/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 19:14:44 by ljoly            ###   ########.fr       */
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

static t_bool	handle_32bit_cpu(t_file f, t_fat_32 fat, const char *arg)
{
	uint32_t	i;
	uint32_t	j;
	char		*cpu_type;

	i = 0;
	fat.arch = f.ptr + sizeof(struct fat_header);
	while (i < fat.nfat_arch)
	{
		if (!access_at(f, f.ptr + swp32(&fat.arch->offset, f.swp)))
			return (FALSE);
		j = 0;
		cpu_type = NULL;
		while (j < sizeof(g_cpu32) / sizeof(*g_cpu32))
		{
			if (fat.arch->cputype == g_cpu32[j].type)
				cpu_type = g_cpu32[j].name;
			j++;
		}
		fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
		fat.magic = *(int *)fat.mach_o.ptr;
		ft_printf("\n%s (for architecture %s):\n", arg, cpu_type);
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
		if (is_cpu_64(swp_signed32(&fat.arch->cputype, f.swp)))
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
		return (handle_32bit_cpu(f, fat, arg));
	return (TRUE);
}
