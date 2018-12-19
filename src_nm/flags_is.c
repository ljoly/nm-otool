/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:14:11 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 19:36:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"

t_bool		is_only_undf(void)
{
	return (g_flags & 1);
}

t_bool		is_no_undf(void)
{
	return ((g_flags >> 1) & 1);
}

t_bool		is_only_names(void)
{
	return ((g_flags >> 2) & 1);
}

t_bool		is_no_sort(void)
{
	return ((g_flags >> 3) & 1);
}

t_bool		is_only_extern(void)
{
	return ((g_flags >> 4) & 1);
}
