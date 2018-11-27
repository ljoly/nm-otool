/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections_64.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:29:29 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/27 15:39:57 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

static t_sect		g_sections[3] = {{SECT_TEXT, 't'},
	{SECT_DATA, 'd'},
	{SECT_BSS, 'b'}};

static t_sect		find_symtype(char *sect_name)
{
	unsigned long	i;
	t_sect			sect;

	i = 0;
	sect.name = sect_name;
	sect.symbol = FALSE;
	while (i < sizeof(g_sections) / sizeof(*g_sections))
	{
		if (ft_strequ(sect_name, g_sections[i].name))
		{
			sect.symbol = g_sections[i].symbol;
			return (sect);
		}
		i++;
	}
	return (sect);
}

static void			store_sections(struct segment_command_64 *seg,
	t_sect *sects, int *s)
{
	uint32_t			i;
	struct section_64	*sect;

	sect = (void *)seg + sizeof(*seg);
	i = 0;
	while (i < seg->nsects)
	{
		sects[*s] = find_symtype(sect->sectname);
		sect = (void *)sect + sizeof(*sect);
		i++;
		*s += 1;
	}
}

t_bool				get_sections_64(t_file f, const char *arg, t_bin *bin)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	int							s;

	if (bin->nsects * sizeof(struct section_64) >= f.size || !bin->nsects)
		return (FALSE);
	if (!(bin->sects = (t_sect*)ft_memalloc(sizeof(t_sect) * bin->nsects)))
	{
		err_cmd(MALLOC, arg);
		return (FALSE);
	}
	bin->lc = (void *)f.ptr + sizeof(struct mach_header_64);
	i = 0;
	s = 0;
	while (i < bin->header->ncmds)
	{
		if (bin->lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)bin->lc;
			if (seg->nsects > 0)
				store_sections(seg, bin->sects, &s);
		}
		bin->lc = (void *)bin->lc + bin->lc->cmdsize;
		i++;
	}
	return (TRUE);
}
