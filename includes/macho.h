/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macho.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 14:03:53 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sections.h"
#include "symbols.h"

/*
** parsing: header, sections, segments and symbols
*/

typedef struct	s_mach
{
	struct mach_header		*header;
	struct load_command		*lc;
	struct symtab_command	*symtab;
	uint32_t				nsects;
	t_sect					*sects;
	t_sym					*syms;
}				t_mach;
