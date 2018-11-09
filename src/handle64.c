/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/09 17:28:19 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static char			get_symtype(uint8_t type, uint8_t n_sect)
{
	char			t;

	t = type & N_TYPE;
	if (t == N_UNDF)
	{
		t = 'u';
	}
	else if (t == N_SECT)
	{
		printf("n_sect = %d\n", n_sect);
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
	char			*strtable;
	struct nlist_64	*symtable;
	uint8_t			symtype;

	symtable = p + symoff;
	strtable = p + stroff;
	i = 0;
	while (i < nsyms)
	{
		symtype = get_symtype(symtable[i].n_type, symtable[i].n_sect);
		if (symtype == 'u' || symtype == 'U')
		{
			printf("%18c %s\n", symtype, strtable + symtable[i].n_un.n_strx);
		}
		else
			printf("%.16llx %c %s\n", symtable[i].n_value, symtype, strtable + symtable[i].n_un.n_strx);
		i++;
	}
}

void				handle_64(char *p, t_bool swap)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	printf("sizeof header = %zu\n", sizeof(*header));
	printf("sizeof lc = %zu\n", sizeof(*lc));
	if (swap)
	{
		ft_putendl("SWAP");
		return ;
	}
	header = (struct mach_header_64 *)p;
	lc = (void *)p + sizeof(*header);
	i = 0;
	printf("ncmds = %d\nsizeofcmds = %d\nflags = %d\n\n", header->ncmds, header->sizeofcmds, header->flags);
	while (i < header->ncmds)
	{
		// printf("lc->cmd = %x\n", lc->cmd);
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			// printf("stroff = %d\n", sym->stroff);
			// printf("nm symbols = %d\n", sym->nsyms);
			print(sym->nsyms, sym->symoff, sym->stroff, p);
			// break ;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}
