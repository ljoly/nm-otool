/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:30:39 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/05 20:16:44 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include <ar.h>

#define AR_NAME_SIZE 20

t_bool			handle_arch(t_file f, const char *arg)
{
	t_file			mach_o;
	struct ar_hdr	*ar;
	struct ranlib	*ranlib;
	uint32_t		magic;

	(void)arg;
	ar = f.ptr + SARMAG;
	ranlib = (void*)ar + sizeof(struct ar_hdr) + AR_NAME_SIZE + sizeof(uint32_t);
	mach_o.ptr = f.ptr + ranlib->ran_off + sizeof(struct ar_hdr) + AR_NAME_SIZE;
	while (access_at(f, mach_o.ptr))
	{
		magic = *(uint32_t*)mach_o.ptr;
		mach_o.size = ft_atoi(ar->ar_size);
		if (ft_strequ((char*)ar + sizeof(struct ar_hdr), "ft_strjoin_and_free.o"))
		{
			ft_printf("\n%s(%s):\n", arg, (char*)ar + sizeof(struct ar_hdr));
			handle_magic(magic, mach_o, arg);
			break;
		}
		ar = (void*)ar + sizeof(struct ar_hdr) + ft_atoi(ar->ar_size);
		mach_o.ptr = (void*)ar + sizeof(struct ar_hdr) + AR_NAME_SIZE;
	}
	return (TRUE);
}
