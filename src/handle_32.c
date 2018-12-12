/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_32.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 18:02:32 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 19:36:52 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		init_data(t_file f, t_mach *o)
{
	o->header = (struct mach_header *)f.ptr;
	o->lc = f.ptr + sizeof(struct mach_header);
	o->symtab = NULL;
	o->sects = NULL;
	o->syms = NULL;
	o->nsects = 0;
}

t_bool			handle_32(t_file f, const char *arg)
{
	t_mach		o;
	uint32_t	sizeof_cmds;
	uint32_t	i;

	init_data(f, &o);
	if (!access_at(f, f.ptr + sizeof(struct mach_header)))
		return (FALSE);
	if (!swp32(&o.header->ncmds, f.swp) && !swp32(&o.header->sizeofcmds, f.swp))
		return (TRUE);
	sizeof_cmds = 0;
	i = 0;
	while (i < o.header->ncmds)
	{
		if (!cmd32_is_consistent(f, &o))
			return (FALSE);
		sizeof_cmds += o.lc->cmdsize;
		o.lc = (void *)o.lc + o.lc->cmdsize;
		i++;
	}
	if (sizeof_cmds != swp32(&o.header->sizeofcmds, f.swp) ||
		!get_sections_32(f, arg, &o))
	{
		return (FALSE);
	}
	o.lc = f.ptr + sizeof(struct mach_header);
	return (handle_syms(f, arg, &o, &get_syms_32));
}
