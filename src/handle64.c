/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/13 19:47:02 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// static char			get_symtype(uint8_t type, uint8_t n_sect)
// {
// 	char			t;

// 	t = type & N_TYPE;
// 	if (t == N_UNDF)
// 	{
// 		t = 'u';
// 	}
// 	else if (t == N_SECT)
// 	{
// 		printf("n_sect = %d\n", n_sect);
// 		t = 't';
// 	}
// 	if (type & N_EXT)
// 	{
// 		t -= 32;
// 	}
// 	return (t);
// }

// static void			print_sym(int nsyms, int symoff, int stroff, void *p)
// {
// 	int				i;
// 	char			*strtable;
// 	struct nlist_64	*symtable;
// 	uint8_t			symtype;

// 	symtable = p + symoff;
// 	strtable = p + stroff;
// 	i = 0;
// 	printf("nsyms = %d\n", nsyms);
// 	while (i < nsyms)
// 	{
// 		symtype = get_symtype(symtable[i].n_type, symtable[i].n_sect);
// 		if (symtype == 'u' || symtype == 'U')
// 		{
// 			printf("%18c %s\n", symtype, strtable + symtable[i].n_un.n_strx);
// 		}
// 		else
// 			printf("%.16llx %c %s\n", symtable[i].n_value, symtype, strtable + symtable[i].n_un.n_strx);
// 		i++;
// 	}
// }

void				handle_64(char *file, t_bool swap)
{
	t_obj						obj;
	uint32_t					i;

	if (swap)
	{
		ft_putendl("SWAP");
		return ;
	}
	obj.header = (struct mach_header *)file;
	obj.lc = (void *)file + sizeof(struct mach_header_64);
	obj.nsects = 0;
	i = 0;
	while (i < obj.header->ncmds)
	{
		if (obj.lc->cmd == LC_SEGMENT_64)
		{
			count_sections(&obj);
		}
		obj.lc = (void *)obj.lc + obj.lc->cmdsize;
		i++;
	}
	printf("NSECTS = %u\n", obj.nsects);
	get_sections(&obj, file);
	i = 0;
	while (i < obj.nsects)
	{
		printf("%c %s\n", obj.sects[i].symbol, obj.sects[i].name);
		i++;
	}
	// i = 0;
	// while (i < obj.header->ncmds)
	// {
	// 	if (obj.lc->cmd == LC_SEGMENT_64)
	// 	{
	// 		get_sections((struct segment_command_64 *)obj.lc);
	// 	}
	// 	else if (obj.lc->cmd == LC_SYMTAB)
	// 	{
	// 		obj.sym = (struct symtab_command *)obj.lc;
	// 		print_sym(obj.sym->nsyms, obj.sym->symoff, obj.sym->stroff, file);
	// 	}
	// 	obj.lc = (void *)obj.lc + obj.lc->cmdsize;
	// 	i++;
	// }
}
