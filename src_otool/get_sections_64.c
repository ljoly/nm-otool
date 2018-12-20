/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections_64.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 13:29:29 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 11:23:22 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool		print_sect_text(t_file f, struct section_64 *sect)
{
	unsigned char	*p;
	uint64_t		i;
	int				j;
	uint32_t		offset;

	p = f.ptr + swp32(&sect->offset, f.swp);
	if (!access_at(f, p + swp64(&sect->size, f.swp)))
		return (FALSE);
	i = 0;
	offset = sect->offset;
	ft_putendl("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		ft_printf("%s%.8x\t", "00000001", offset);
		j = -1;
		while (++j < 16)
		{
			ft_printf("%.2x ", p[j]);
		}
		ft_putchar('\n');
		p += 16;
		offset += 16;
		i += 16;
	}
	return (TRUE);
}

static t_bool		find_sect_text(t_file f, struct segment_command_64 *seg)
{
	uint32_t			i;
	struct section_64	*sect;

	sect = (void *)seg + sizeof(*seg);
	i = 0;
	while (i < seg->nsects)
	{
		if (!ft_strncmp(sect->sectname, SECT_TEXT, ft_strlen(sect->sectname)))
		{
			return (print_sect_text(f, sect));
		}
		sect = (void *)sect + sizeof(*sect);
		i++;
	}
	return (FALSE);
}

t_bool				get_sections_64(t_file f, const char *arg, t_mach *o)
{
	uint32_t					i;
	struct segment_command_64	*seg;

	(void)arg;
	o->lc = (void *)f.ptr + sizeof(struct mach_header_64);
	i = 0;
	while (i < o->header->ncmds)
	{
		if (o->lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)o->lc;
			if (seg->nsects > 0 &&
				!ft_strncmp(seg->segname, SEG_TEXT, ft_strlen(seg->segname)))
			{
				return (find_sect_text(f, seg));
			}
		}
		o->lc = (void *)o->lc + o->lc->cmdsize;
		i++;
	}
	return (FALSE);
}
