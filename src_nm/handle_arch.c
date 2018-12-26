/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:30:39 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/26 18:40:38 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include <ar.h>

static uint32_t			get_ar_name_size(struct ar_hdr *ar)
{
	uint32_t			size;

	size = 0;
	if (!ft_strncmp(ar->ar_name, AR_EFMT1, ft_strlen(AR_EFMT1)))
		size = ft_atoi(ar->ar_name + ft_strlen(AR_EFMT1));
	return (size);
}

static void				*get_first_o(t_file f, struct ar_hdr **ar,
	uint32_t *ar_name_size)
{
	struct ranlib	*ranlib;
	uint32_t		offset;

	ranlib = (void*)*ar + sizeof(struct ar_hdr) + *ar_name_size;
	if (!access_at(f, (void*)ranlib + sizeof(uint32_t)))
		return (NULL);
	if (!*(uint32_t*)ranlib)
	{
		offset = (void*)ranlib - f.ptr + 8;
	}
	else
	{
		ranlib = (void*)ranlib + sizeof(uint32_t);
		offset = ranlib->ran_off;
	}
	*ar = f.ptr + offset;
	if (!access_at(f, (void*)*ar + sizeof(struct ar_hdr)))
		return (NULL);
	*ar_name_size = get_ar_name_size(*ar);
	return ((void*)*ar + sizeof(struct ar_hdr)
		+ *ar_name_size);
}

static struct ar_hdr	*init_data(t_file f, uint32_t *ar_name_size,
	t_file *mach_o)
{
	struct ar_hdr	*ar;

	ar = f.ptr + SARMAG;
	if (!access_at(f, (void*)ar + sizeof(struct ar_hdr)))
		return (NULL);
	*ar_name_size = get_ar_name_size(ar);
	if (!(mach_o->ptr = get_first_o(f, &ar, ar_name_size)))
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
		ar_name_size ? ft_printf("\n%s(%s):\n", arg, (char*)ar + sizeof(struct ar_hdr)) :
			ft_printf("\n%s(%s):\n", arg, ar->ar_name);
		handle_magic(magic, mach_o, arg);
		ar = (void*)ar + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
		if (!access_at(f, (void*)ar + sizeof(struct ar_hdr)))
		{
			break ;
		}
		ar_name_size = get_ar_name_size(ar);
		mach_o.ptr = (void*)ar + sizeof(struct ar_hdr) + ar_name_size;
	}
	return (TRUE);
}
