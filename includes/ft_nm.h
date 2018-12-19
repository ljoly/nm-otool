/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 21:13:44 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <sys/stat.h>
# include "sections.h"
# include "symbols.h"
# include "macho.h"

/*
** file data
*/

typedef struct	s_file
{
	void		*ptr;
	uint64_t	size;
	t_bool		swp;
}				t_file;

t_bool			access_at(t_file f, const void *ptr);

t_bool			handle_arg(const char *arg, int *fd);

t_bool			handle_64(t_file f, const char *arg);
t_bool			handle_32(t_file f, const char *arg);
t_bool			handle_fat_32(t_file f, const char *arg);
t_bool			handle_fat_64(t_file f, const char *arg);
t_bool			handle_arch(t_file f, const char *arg);

uint32_t		swp32(uint32_t *val, t_bool swp);
uint64_t		swp64(uint64_t *val, t_bool swp);
int				swp_signed32(int *val, t_bool swp);

t_bool			cmd64_is_consistent(t_file f, t_mach *o);
t_bool			cmd32_is_consistent(t_file f, t_mach *o);

t_bool			get_sections_64(t_file f, const char *arg, t_mach *o);
t_bool			get_sections_32(t_file f, const char *arg, t_mach *o);

t_bool			handle_syms(t_file f, const char *arg, t_mach *o,
	t_bool (*print_sym)(t_file f, t_mach *o));
t_bool			get_syms_64(t_file f, t_mach *o);
t_bool			get_syms_32(t_file f, t_mach *o);

void			sort_syms(t_sym *syms, uint32_t size);
void			print_syms(const t_mach o, t_bool arch_64);

#endif
