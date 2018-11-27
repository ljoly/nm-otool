/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_consistency.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 17:49:18 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/27 18:36:35 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

/*
** checking offsets:
**   f.ptr is the address of the mapped file
**   ptr is the pointer to check
*/

t_bool		access_at(t_file f, const void *ptr)
{
	if (ptr - f.ptr < 0 && ptr - f.ptr > f.size)
	{
		ft_putendl("NO_ACCESS");
		return (FALSE);
	}
	return (TRUE);
	// return (ptr - g_file >= 0 && ptr - g_file <= g_size);
}

/*
** checking the reliability of:
**   sizeof struct segment/sections
**   cmdsize
**   nsects
*/

t_bool		check_sects_64(t_bin *bin)
{
	struct segment_command_64	*seg;

	seg = (struct segment_command_64*)bin->lc;
	if (seg->nsects * sizeof(struct section_64) + sizeof(*seg) != seg->cmdsize)
	{
		return (FALSE);
	}
	bin->nsects += seg->nsects;
	return (TRUE);
}

t_bool		cmd_is_consistent(t_file f, t_bin *bin, uint32_t lc_segment,
	t_bool (*check)(t_bin *bin))
{
	if (bin->lc->cmdsize <= 0 || !access_at(f, (void*)bin->lc + bin->lc->cmdsize))
	{
		return (FALSE);
	}
	if (bin->lc->cmd == lc_segment && !check(bin))
	{
		return (FALSE);
	}
	return (TRUE);
}
