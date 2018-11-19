/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 20:07:08 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

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
	bin.nsects = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (!access_at((void*)bin.lc + bin.lc->cmdsize))
			return (FALSE);
		if (bin.lc->cmd == LC_SEGMENT_64)
			count_sections_64(&bin);
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	get_sections_64(&bin, g_file);
	i = 0;
	bin.lc = g_file + sizeof(struct mach_header_64);
	return (get_syms(bin, &print_sym64));
}
