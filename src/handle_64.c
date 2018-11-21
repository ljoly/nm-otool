/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/21 19:32:23 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

static void		swap64(void)
{
	ft_putendl("SWAP");
	exit(0);
}

t_bool			handle_64(t_bool swap)
{
	t_bin		bin;
	uint32_t	i;

	if (swap)
		swap64();
	bin.header = (struct mach_header *)g_file;
	if (!access_at(g_file + sizeof(struct mach_header_64)))
		return (FALSE);
	bin.lc = g_file + sizeof(struct mach_header_64);
	bin.sects = NULL;
	bin.nsects = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (!is_consistent(&bin, &check_sects_64))
			return (free_memory(bin.sects, NULL, FALSE));
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	if (bin.nsects * sizeof(struct section_64) >= g_size)
		return (free_memory(bin.sects, NULL, FALSE));
	get_sections_64(&bin, g_file);
	bin.lc = g_file + sizeof(struct mach_header_64);
	return (handle_syms(&bin, &get_syms64));
}
