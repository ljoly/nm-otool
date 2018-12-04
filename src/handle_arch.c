/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:30:39 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/04 18:30:31 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <ar.h>

t_bool			handle_arch(t_file f, const char *arg)
{
	void			*p;
	// struct ar_hdr	*ar;
	struct ranlib	*ranlib;
	uint32_t		ranlib_size;
	uint32_t		i;

	(void)arg;
	p = f.ptr + SARMAG + sizeof(struct ar_hdr) + 20;
	if (!access_at(f, p))
		return (FALSE);
	ranlib_size = *(uint32_t*)p / sizeof(struct ranlib);
	p = p + sizeof(uint32_t);
	ranlib = (struct ranlib*)p;
	i = 0;
	while (i < ranlib_size)
	{
		// if (!access_at(f, ranlib + sizeof(*ranlib)))
		// 	return (FALSE);
		// ft_printf("%d: %x && off = %x\n", i, ranlib[i].ran_un.ran_strx, ranlib[i].ran_off);
		p = f.ptr + ranlib[i].ran_off + sizeof(struct ar_hdr);
		ft_printf("offset = %u: %s\n", ranlib[i].ran_off, (char*)p);
		// ranlib = (void*)ranlib + sizeof(*ranlib);
		// exit(0);
		i++;
	}
	return (TRUE);
}
