/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:57:52 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 16:10:37 by ljoly            ###   ########.fr       */
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

static void			print_arg(int magic, const char *arg)
{
	if (magic == g_nums[5].num || magic == g_nums[7].num)
		return ;
	else if (magic == AR_MAG)
		ft_printf("Archive : %s\n", arg);		
	else
		ft_printf("%s:\n", arg);
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

t_bool				handle_magic_otool(int magic, t_file f, const char *arg,
	t_bool print)
{
	t_bool			valid_file;
	unsigned long	i;

	valid_file = FALSE;
	if (!handle_ar_magic(&magic, f))
	{
		err_cmd(FORMAT, arg);
		return (FALSE);
	}
	i = 0;
	while (i < sizeof(g_nums) / sizeof(*g_nums))
	{
		if (magic == g_nums[i].num)
		{
			if (print)
				print_arg(magic, arg);
			f.swp = g_nums[i].swp;
			if (g_nums[i].cmd(f, arg))
				valid_file = TRUE;
			break ;
		}
		i++;
	}
	if (!valid_file)
		err_cmd(FORMAT, arg);
	return (valid_file);
}
