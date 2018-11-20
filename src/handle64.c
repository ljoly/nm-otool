/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/20 18:57:02 by ljoly            ###   ########.fr       */
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
		if (!bin.lc->cmdsize || !access_at((void*)bin.lc + bin.lc->cmdsize))
			return (free_memory(bin.sects, NULL, FALSE));
		if (bin.lc->cmd == LC_SEGMENT_64)
			// HERE
			if (!count_sects_64(&bin))
			// HERE
				return (free_memory(bin.sects, NULL, FALSE));
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	if (bin.nsects * sizeof(struct section_64) > g_size ||
		!get_sections_64(&bin, g_file))
		return (free_memory(bin.sects, NULL, FALSE));
	bin.lc = g_file + sizeof(struct mach_header_64);
	return (get_syms(&bin, &print_sym64));
}
