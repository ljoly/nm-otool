/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/13 16:52:31 by ljoly            ###   ########.fr       */
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

int				g_exit_status;

typedef struct			s_obj
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	uint32_t				nsects;
	t_sect					*sects;
}						t_obj;

void					handle_arg(char *arg, int *fd);
void					handle_64(char *p, t_bool swap);
void					count_sections(t_obj *obj);
void					get_sections(t_obj *obj, char *file);

#endif