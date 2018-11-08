/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/08 19:57:34 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char			get_symtype(uint8_t type)
{
	char			t;

	t = type & N_TYPE;
	if (t == N_UNDF)
	{
		t = 'u';
	}
	else if (t == N_SECT)
	{
		t = 't';
	}
	if (type & N_EXT)
	{
		t -= 32;
	}
	return (t);
}

static void			print(int nsyms, int symoff, int stroff, void *p)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;
	uint8_t			symtype;

	array = p + symoff;
	stringtable = p + stroff;
	i = 0;
	while (i < nsyms)
	{
		symtype = get_symtype(array[i].n_type);
		if (symtype == 'u' || symtype == 'U')
		{
			printf("%18c %s\n", symtype, stringtable + array[i].n_un.n_strx);
		}
		else
			printf("%.16llx %c %s\n", array[i].n_value, symtype, stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void				handle_64(char *p, t_bool swap)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	if (swap)
	{
		ft_putendl("SWAP");
		return ;
	}
	header = (struct mach_header_64 *)p;
	lc = (void *)p + sizeof(*header);
	i = 0;
	printf("ncmds = %d\nsizeofcmds = %d\nflags = %d\n", header->ncmds, header->sizeofcmds, header->flags);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			printf("stroff = %d\n", sym->stroff);
			// printf("nm symbols = %d\n", sym->nsyms);
			print(sym->nsyms, sym->symoff, sym->stroff, p);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
