/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:57:52 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/27 18:00:35 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

static t_magic		g_nums[] = {// {MH_MAGIC, NOSWAP, handle_32},
// {MH_CIGAM, SWAP, handle_32},
	{MH_MAGIC_64, NOSWAP, handle_64},
	{MH_CIGAM_64, SWAP, handle_64},
	{FAT_MAGIC, NOSWAP, handle_fat32},
	{FAT_CIGAM, SWAP, handle_fat32},
	// {FAT_MAGIC_64, NOSWAP, handle_fat64},
	// {FAT_CIGAM_64, NOSWAP, handle_fat64},
};

void				handle_magic(const int magic, t_file f, const char *arg)
{
	t_bool			valid_file;
	unsigned long	i;

	valid_file = FALSE;
	i = 0;
	while (i < sizeof(g_nums) / sizeof(*g_nums))
	{
		if ((unsigned int)magic == g_nums[i].num)
		{
			if (g_nums[i].cmd(f, arg, g_nums[i].swap))
				valid_file = TRUE;
			break ;
		}
		i++;
	}
	if (!valid_file)
	{
		err_cmd(FORMAT, arg);
	}
}
