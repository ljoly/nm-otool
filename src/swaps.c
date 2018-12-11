/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   swaps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/22 17:27:54 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/11 19:16:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

uint32_t	swp32(uint32_t *val, t_bool swp)
{
	if (swp)
	{
		*val = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF);
		*val = (*val << 16) | (*val >> 16);
	}
	return (*val);
}

int			swp_signed32(int *val, t_bool swp)
{
	if (swp)
	{
    	*val = ((*val << 8) & 0xFF00FF00) | ((*val >> 8) & 0xFF00FF );
		*val = (*val << 16) | ((*val >> 16) & 0xFFFF);
	}
	return (*val);
}

uint64_t	swp64(uint64_t *val, t_bool swp)
{
	if (swp)
	{
		*val = ((*val << 8) & 0xFF00FF00FF00FF00ULL) |
			((*val >> 8) & 0x00FF00FF00FF00FFULL);
		*val = ((*val << 16) & 0xFFFF0000FFFF0000ULL) |
			((*val >> 16) & 0x0000FFFF0000FFFFULL);
		*val = (*val << 32) | (*val >> 32);
	}
	return (*val);
}