/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 15:05:09 by ljoly            ###   ########.fr       */
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
# include "macho.h"

/*
** return value
*/

int				g_exit_status;

/*
** file data
*/

typedef struct	s_file
{
	void		*ptr;
	uint32_t	size;
	t_bool		swap;
}				t_file;

t_bool			access_at(t_file f, const void *ptr);

void			handle_arg(const char *arg, int *fd);
t_bool			handle_64(t_file f, const char *arg);
t_bool			handle_fat_32(t_file f, const char *arg);
t_bool			handle_fat_64(t_file f, const char *arg);

uint32_t		swap_32(uint32_t val, t_bool swap);

t_bool			cmd64_is_consistent(t_file f, t_mach *o);
t_bool			cmd32_is_consistent(t_file f, t_mach *o);

t_bool			get_sections_64(t_file f, const char *arg, t_mach *o);

t_bool			handle_syms(t_file f, const char *arg, t_mach *o,
	t_bool (*print_sym)(t_file f, t_mach *o));
t_bool			get_syms64(t_file f, t_mach *o);

void			sort_syms(t_sym *syms, uint32_t size);

void			print_syms(const t_mach o);

#endif
