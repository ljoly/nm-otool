/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_sections_32.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 19:57:48 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 16:31:17 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static t_bool		handle_ppc(t_file f, struct section *sect)
{
	unsigned char	*p;
	uint32_t		i;
	uint32_t		offset;
	uint32_t		align;

	p = f.ptr + swp32(&sect->offset, f.swp);
	if (!access_at(f, p + swp32(&sect->size, f.swp)))
		return (FALSE);
	i = 0;
	offset = swp32(&sect->addr, f.swp) - 16;
	align = 16 / (swp32(&sect->align, f.swp) * sect->align);
	ft_putstr("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		if (i % 16 == 0)
		{
			ft_printf("\n%.8x\t", offset += 16);
		}
		ft_printf("%.2x", p[i]);
		i++;
		if (i % align == 0)
			ft_printf(" ");
	}
	ft_putchar('\n');
	return (TRUE);
}

static t_bool		print_sect_text(t_file f, struct section *sect)
{
	unsigned char	*p;
	uint32_t		i;
	uint32_t		offset;
	uint32_t		magic;

	magic = *(uint32_t*)f.ptr;
	if (magic == MH_CIGAM)
		return (handle_ppc(f, sect));
	p = f.ptr + swp32(&sect->offset, f.swp);
	if (!access_at(f, p + swp32(&sect->size, f.swp)))
		return (FALSE);
	i = 0;
	offset = swp32(&sect->addr, f.swp) - 16;
	ft_putstr("Contents of (__TEXT,__text) section");
	while (i < sect->size)
	{
		if (i % 16 == 0)
			ft_printf("\n%.8x\t", offset += 16);
		ft_printf("%.2x ", p[i]);
		i++;
	}
	ft_putchar('\n');
	return (TRUE);
}

static t_bool		find_sect_text(t_file f, struct segment_command *seg)
{
	uint32_t			i;
	struct section		*sect;

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

t_bool				get_sections_32(t_file f, const char *arg, t_mach *o)
{
	uint32_t					i;
	struct segment_command		*seg;

	(void)arg;
	o->lc = (void *)f.ptr + sizeof(struct mach_header);
	i = 0;
	while (i < o->header->ncmds)
	{
		if (o->lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)o->lc;
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
