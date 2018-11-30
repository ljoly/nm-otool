/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/30 17:08:42 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"
#include "handle_magic.h"

static t_file	get_mach_o_file(void *file, struct fat_arch *arch)
{
	t_file		mach_o;

	// printf("ptr = %p\n", file + arch->offset);
	mach_o.ptr = file + arch->offset;
	mach_o.size = arch->size;
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
			ft_putendl("CPU FOUND");
			if (!access_at(f, f.ptr + arch->offset))
				return (FALSE);
			mach_o = get_mach_o_file(f.ptr, arch);
			ft_putendl("HAHAHA");
			magic = *(int *)mach_o.ptr;
			handle_magic(magic, mach_o, arg);
			break ;
		}
		// else
			// ft_printf("cpu_type = %zu\n", swap_32(arch->cputype, swap));
		arch = (void*)arch + sizeof(*arch);
		i++;
	}
	return (TRUE);
	// bin.lc = g_file + sizeof(struct mach_header_64);
	// bin.sects = NULL;
	// bin.nsects = 0;
	// i = 0;
	// while (i < bin.header->ncmds)
	// {
	// 	if (!is_consistent(&bin, &check_sects_64))
	// 		return (free_memory(bin.sects, NULL, FALSE));
	// 	bin.lc = (void *)bin.lc + bin.lc->cmdsize;
	// 	i++;
	// }
	// if (bin.nsects * sizeof(struct section_64) >= g_size)
	// 	return (free_memory(bin.sects, NULL, FALSE));
	// get_sections_64(&bin, g_file);
	// bin.lc = g_file + sizeof(struct mach_header_64);
	// return (handle_syms(&bin, &get_syms64));
}
