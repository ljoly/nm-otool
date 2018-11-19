/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:57:52 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 17:33:43 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

static t_magic		g_nums[] = {{MH_MAGIC_64, NOSWAP, handle_64},
	{MH_CIGAM_64, SWAP, handle_64}};
	// {MH_MAGIC, FALSE, handle_32},
	// {MH_CIGAM, TRUE, handle_32},

void				handle_magic(const char *arg)
{
	unsigned int	magic;
	t_bool			valid_file;
	unsigned long	i;

	magic = *(int *)g_file;
	valid_file = FALSE;
	i = 0;
	while (i < sizeof(g_nums) / sizeof(*g_nums))
	{
		if (magic == g_nums[i].num)
		{
			if (g_nums[i].cmd(g_nums[i].swap))
				valid_file = TRUE;
			break ;
		}
		i++;
	}
	if (!valid_file)
	{
		err_usage(FORMAT, arg);
	}
}