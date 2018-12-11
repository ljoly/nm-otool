/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:30:39 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/11 15:36:19 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include <ar.h>

static struct ar_hdr	*init_data(t_file f, uint32_t *ar_name_size,
	t_file *mach_o)
{
	struct ar_hdr	*ar;
	struct ranlib	*ranlib;

	ar = f.ptr + SARMAG;
	if (!access_at(f, (void*)ar + sizeof(struct ar_hdr)))
		return (NULL);
	*ar_name_size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
	ranlib = (void*)ar + sizeof(struct ar_hdr) + *ar_name_size
		+ sizeof(uint32_t);
	if (!access_at(f, ranlib))
		return (NULL);
	mach_o->ptr = f.ptr + ranlib->ran_off + sizeof(struct ar_hdr)
		+ *ar_name_size;
	ar = (void*)ar + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
	if (!access_at(f, (void*)ar + sizeof(struct ar_hdr)))
		return (NULL);
	return (ar);
}

t_bool					handle_arch(t_file f, const char *arg)
{
	t_file			mach_o;
	struct ar_hdr	*ar;
	uint32_t		ar_name_size;
	uint32_t		magic;

	if (!(ar = init_data(f, &ar_name_size, &mach_o)))
		return (FALSE);
	while (access_at(f, mach_o.ptr))
	{
		magic = *(uint32_t*)mach_o.ptr;
		mach_o.size = ft_atoi(ar->ar_size);
		ft_printf("\n%s(%s):\n", arg, (char*)ar + sizeof(struct ar_hdr));
		handle_magic(magic, mach_o, arg);
		ar = (void*)ar + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
		if (!access_at(f, (void*)ar + sizeof(struct ar_hdr)))
		{
			break ;
		}
		ar_name_size = ft_atoi(ft_strchr(ar->ar_name, '/') + 1);
		mach_o.ptr = (void*)ar + sizeof(struct ar_hdr) + ar_name_size;
	}
	return (TRUE);
}
