/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 12:10:57 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/10 15:06:51 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_bool		access_at(t_file f, const void *ptr)
{
	// if (!(ptr - f.ptr >= 0 && ptr < f.ptr + f.size))
	// {
	// 	ft_printf("file = %u\nptr max = %u\nptr = %u\n", f.ptr, f.ptr + f.size, ptr);
	// }
	return (ptr - f.ptr >= 0 && ptr < f.ptr + f.size);
}
