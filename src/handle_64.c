/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_64.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/22 18:22:36 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

static void		swap64(void)
{
	ft_putendl("SWAP64");
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
	i = 1000;
	while (i < bin.header->ncmds)
	{
		ft_putendl("COUCOU");
		if (!is_consistent(&bin, &check_sects_64))
			return (free_memory(bin.sects, NULL, FALSE));
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	// printf("sects = %d\n", bin.nsects);
	if (bin.nsects * sizeof(struct section_64) >= g_size)
		return (free_memory(bin.sects, NULL, FALSE));
	// rm g_file
	get_sections_64(&bin, g_file);
	bin.lc = g_file + sizeof(struct mach_header_64);
	return (handle_syms(&bin, &get_syms64));
}
