/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:57:52 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/06 16:04:15 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

t_bool				handle_magic(char *p)
{
	unsigned int	magic_number;

	magic_number = *(int *)p;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(p);
	}
	else
	{
		return (FALSE);
	}
	return (TRUE);
}