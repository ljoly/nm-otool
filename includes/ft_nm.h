/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/26 15:20:49 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <sys/stat.h>
# include "sections.h"
# include "symbols.h"

/*
** return value
*/

int				g_exit_status;

/*
** file data
*/

void			*g_file;
uint32_t		g_size;
t_bool			access_at(const void *ptr);

/*
** parsing: header, sections, segments and symbols
*/

typedef struct	s_bin
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*symtab;
	uint32_t				nsects;
	t_sect					*sects;
	t_sym					*syms;
}				t_bin;

void			handle_arg(const char *arg, int *fd);
t_bool			handle_64(t_bool swap);
t_bool			handle_fat32(t_bool swap);

uint32_t		swap_32(uint32_t val);

t_bool			is_consistent(t_bin *bin, uint32_t lc_segment,
	t_bool (*check)(t_bin *bin));

t_bool			check_sects_64(t_bin *bin);
t_bool			get_sections_64(t_bin *bin);

t_bool			handle_syms(t_bin *bin, t_bool (*print_sym)(t_bin *bin));
t_bool			get_syms64(t_bin *bin);

void			sort_syms(t_sym *syms, uint32_t size);

void			print_syms(const t_bin bin);

#endif
