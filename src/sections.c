/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sections.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:29:29 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/13 19:48:41 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_sect		g_sections[] = {{SECT_TEXT,'t'},
	{SECT_DATA, 'd'},
	{SECT_BSS, 'b'},
	{SECT_COMMON, 'c'}};

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
	
	if (!seg->nsects)
		return ;
	sect = (void *)seg + sizeof(*seg);
	i = 0;
	while (i < seg->nsects)
	{
		// printf("segname = %s && sectname = %s\n", sect->segname, sect->sectname);
		sects[*s] = find_symtype(sect->sectname);
		// if (sects[*s].symbol == FALSE)
		// sect[*s].symbol = 
		sect = (void *)sect + sizeof(*sect);
		i++;
		*s += 1;
	}
}

void				get_sections(t_obj *obj, char *file)
{
	uint32_t					i;
	struct segment_command_64	*seg;
	int							s;

	obj->sects = (t_sect*)ft_memalloc(sizeof(t_sect) * obj->nsects);
	obj->lc = (void *)file + sizeof(struct mach_header_64);
	i = 0;
	s = 0;
	while (i < obj->header->ncmds)
	{
		if (obj->lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)obj->lc;
			store_sections(seg, obj->sects, &s);
		}
		obj->lc = (void *)obj->lc + obj->lc->cmdsize;
		i++;
	}
}

void				count_sections(t_obj *obj)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)obj->lc;
	obj->nsects += seg->nsects;
}