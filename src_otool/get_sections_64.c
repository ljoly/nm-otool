/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:29:29 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 17:27:14 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

static t_sect		g_sections[3] = {
	{SECT_TEXT, 't'},
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
		if (!ft_strncmp(sect_name, g_sections[i].name,
			sizeof((struct section_64*)0)->sectname))
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

t_bool				get_sections_64(t_file f, const char *arg, t_mach *o)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	int							s;

	if (!(o->sects = (t_sect*)ft_memalloc(sizeof(t_sect) * o->nsects)))
	{
		err_cmd(MALLOC, arg);
		return (FALSE);
	}
	o->lc = (void *)f.ptr + sizeof(struct mach_header_64);
	i = 0;
	s = 0;
	while (i < o->header->ncmds)
	{
		if (o->lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)o->lc;
			if (seg->nsects > 0)
				store_sections(seg, o->sects, &s);
		}
		o->lc = (void *)o->lc + o->lc->cmdsize;
		i++;
	}
	return (TRUE);
}
