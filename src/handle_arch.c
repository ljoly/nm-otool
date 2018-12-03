/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_arch.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 16:30:39 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 19:42:10 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include <ar.h>

t_bool			handle_arch(t_file f, const char *arg)
{
	void			*p;
	struct ar_hdr	*ar;
	struct ranlib	*ranlib;
	uint64_t		ranlib_size;
	uint64_t		i;

	(void)arg;
	p = f.ptr + SARMAG + sizeof(*ar);
	// ft_printf("sizeof struct ar = %zu && p = %u\n", sizeof(*ar), p);
	ar = f.ptr + SARMAG;
	ft_putendl(ar->ar_fmag);
	if (!access_at(f, p))
		return (FALSE);
	ranlib_size = *(uint64_t*)p;
	p = p + sizeof(uint64_t);
	ranlib = (struct ranlib*)p;
	i = 0;
	ft_printf("size = %llu\n", ranlib_size);
	while (i < ranlib_size)
	{
		if (!access_at(f, ranlib + sizeof(*ranlib)))
			return (FALSE);
		ranlib = (void*)ranlib + sizeof(*ranlib);
		i++;
	}
	return (TRUE);
}
