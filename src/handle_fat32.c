/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_fat32.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 19:31:58 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/21 19:52:14 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

t_bool		handle_fat32(t_bool swap)
{
	struct fat_header	*header;

	if (swap)
		ft_putendl("SWAP");
	header = (struct fat_header *)g_file;
	if (!access_at(g_file + sizeof(*header)))
	{
		return (FALSE);
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
