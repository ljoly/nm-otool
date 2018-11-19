/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 12:14:58 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>
# include "sections.h"
# include "symbols.h"

int						g_exit_status;

void					*g_file;
int						g_size;
t_bool					check_access(const void *ptr);

typedef struct			s_bin
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*symtab;
	uint32_t				nsects;
	t_sect					*sects;
	t_sym					*syms;
}						t_bin;

void					handle_arg(const char *arg, int *fd);

void					handle_64(t_bool swap);
void					count_sections_64(t_bin *bin);
void					get_sections_64(t_bin *bin, char *file);

void					get_syms(t_bin bin, void (*print_sym)(t_bin *bin));
void					print_sym64(t_bin *bin);
// void					print_sym32(t_bin *bin);

void					sort_syms(t_sym *syms, uint32_t size);

#endif
