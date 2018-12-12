/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:00:22 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 19:04:42 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAT_H
# define FAT_H

# include "ft_nm.h"

typedef struct	s_fat_32
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	uint32_t			nfat_arch;
	t_file				mach_o;
	int					magic;
	t_bool				cpu_type_found;
}				t_fat_32;

typedef struct	s_fat_64
{
	struct fat_header	*header;
	struct fat_arch_64	*arch;
	uint32_t			nfat_arch;
	t_file				mach_o;
	int					magic;
	t_bool				cpu_type_found;
}				t_fat_64;

typedef struct	s_cpu
{
	int			type;
	char		*name;
}				t_cpu;

t_cpu			g_cpu32[4];

t_bool			is_cpu_64(const int type);

#endif
