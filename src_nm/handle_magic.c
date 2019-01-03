/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:57:52 by ljoly             #+#    #+#             */
/*   Updated: 2019/01/03 21:10:54 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_magic.h"
#include "error.h"

static t_magic		g_nums[9] = {
	{MH_MAGIC_64, NOSWAP, handle_64},
	{MH_CIGAM_64, SWAP, handle_64},
	{MH_MAGIC, NOSWAP, handle_32},
	{MH_CIGAM, SWAP, handle_32},
	{FAT_MAGIC, NOSWAP, handle_fat_32},
	{FAT_CIGAM, SWAP, handle_fat_32},
	{FAT_MAGIC_64, NOSWAP, handle_fat_64},
	{FAT_CIGAM_64, NOSWAP, handle_fat_64},
	{AR_MAG, NOSWAP, handle_arch},
};

static void			handle_error(t_bool *error_seen, const char *arg)
{
	err_cmd(FORMAT, arg);
	*error_seen = TRUE;
}

static t_bool		handle_ar_magic(int *magic, t_file f)
{
	if (!access_at(f, f.ptr + SARMAG))
	{
		return (FALSE);
	}
	if (*(int64_t*)f.ptr == AR_MAGIC)
	{
		*magic = AR_MAG;
	}
	return (TRUE);
}

t_bool				handle_magic(int magic, t_file f, const char *arg)
{
	t_bool			valid_file;
	static t_bool	error_seen = FALSE;
	unsigned long	i;

	valid_file = FALSE;
	if (!handle_ar_magic(&magic, f))
	{
		handle_error(&error_seen, arg);
		return (FALSE);
	}
	i = 0;
	while (i < sizeof(g_nums) / sizeof(*g_nums))
	{
		if (magic == g_nums[i].num)
		{
			f.swp = g_nums[i].swp;
			if (g_nums[i].cmd(f, arg))
				valid_file = TRUE;
			break ;
		}
		i++;
	}
	if (!valid_file && !error_seen)
		handle_error(&error_seen, arg);
	return (valid_file);
}
