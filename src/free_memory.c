/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:09:14 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/20 18:00:00 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"

t_bool		free_memory(t_sect *sects, t_sym *syms, t_bool status)
{
	if (sects)
	{
		free(sects);
	}
	if (syms)
	{
		free(syms);
	}
	return (status);
}