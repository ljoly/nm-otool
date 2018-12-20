/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags_is.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 19:14:11 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 13:42:13 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"

t_bool		is_only_undf(void)
{
	return (g_flags & ONLY_UNDF);
}

t_bool		is_no_undf(void)
{
	return (g_flags & NO_UNDF);
}

t_bool		is_only_names(void)
{
	return (g_flags & ONLY_NAMES);
}

t_bool		is_no_sort(void)
{
	return (g_flags & NO_SORT);
}

t_bool		is_only_extern(void)
{
	return (g_flags & ONLY_EXTERN);
}
