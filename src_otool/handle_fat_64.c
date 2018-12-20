/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 15:04:04 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 17:13:32 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "fat.h"
#include "handle_magic.h"

static void		print_name_o(t_fat_64 fat, const char *arg, char *cpu_type)
{
	if (fat.nfat_arch == 1)
		ft_printf("%s:\n", arg, cpu_type);
	else
		ft_printf("%s (architecture %s):\n", arg, cpu_type);
}

static t_file	get_mach_o_file(void *file, struct fat_arch_64 *arch,
	t_bool swp)
{
	t_file		mach_o;

	mach_o.ptr = file + arch->offset;
	mach_o.size = swp64(&arch->size, swp);
	return (mach_o);
}

static t_bool	handle_cpu_type(t_file f, t_fat_64 fat, const char *arg)
{
	uint32_t	i;
	uint32_t	j;
	char		*cpu_type;

	i = 0;
	fat.arch = f.ptr + sizeof(struct fat_header);
	while (i < fat.nfat_arch)
	{
		if (!access_at(f, f.ptr + swp64(&fat.arch->offset, f.swp)))
			return (FALSE);
		j = -1;
		cpu_type = NULL;
		while (++j < sizeof(g_cpu32) / sizeof(*g_cpu32))
		{
			if (fat.arch->cputype == g_cpu32[j].type)
				cpu_type = g_cpu32[j].name;
		}
		fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
		fat.magic = *(int *)fat.mach_o.ptr;
		print_name_o(fat, arg, cpu_type);
		handle_magic_otool(fat.magic, fat.mach_o, arg, FALSE);
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
		i++;
	}
	return (TRUE);
}

static void		init_data(t_file f, t_fat_64 *fat)
{
	fat->cpu_type_found = FALSE;
	fat->header = (struct fat_header *)f.ptr;
	fat->nfat_arch = swp32(&fat->header->nfat_arch, f.swp);
	fat->arch = f.ptr + sizeof(*fat->header);
}

t_bool			handle_fat_64(t_file f, const char *arg)
{
	t_fat_64	fat;
	uint32_t	i;

	init_data(f, &fat);
	if (!access_at(f, f.ptr + sizeof(*fat.header)))
		return (FALSE);
	i = -1;
	while (++i < fat.nfat_arch)
	{
		if (!access_at(f, (void*)fat.arch + sizeof(*fat.arch)))
			return (FALSE);
		if (is_cpu_64(swp_signed32(&fat.arch->cputype, f.swp)))
		{
			fat.cpu_type_found = TRUE;
			if (!access_at(f, f.ptr + swp64(&fat.arch->offset, f.swp)))
				return (FALSE);
			fat.mach_o = get_mach_o_file(f.ptr, fat.arch, f.swp);
			fat.magic = *(int *)fat.mach_o.ptr;
			ft_printf("%s:\n", arg);
			handle_magic_otool(fat.magic, fat.mach_o, arg, FALSE);
			break ;
		}
		fat.arch = (void*)fat.arch + sizeof(*fat.arch);
	}
	return (fat.cpu_type_found ? TRUE : handle_cpu_type(f, fat, arg));
}
