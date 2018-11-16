/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle64.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 15:53:59 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/16 17:04:09 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint8_t		get_symtype(uint8_t n_type, uint8_t n_sect, t_sect *sects)
{
	uint8_t			t;

	// printf("n_sect = %d ; n_type = %d ; n_value = %llu\n", n_sect, n_type, n_value);
	if (n_type & N_STAB)
	{
		return (FALSE);
	}
	t = n_type & N_TYPE;
	if (t == N_UNDF)
	{
		t = sects[n_sect - 1].symbol ? 'c' : 'u';
	}
	else if (t == N_ABS)
	{
		t = 'a';
	}
	else if (t == N_SECT)
	{
		t = sects[n_sect - 1].symbol ? sects[n_sect - 1].symbol : 's';
	}
	if (n_type & N_EXT)
	{
		t -= 32;
	}
	return (t);
}

static void			sort_syms(t_sym *syms, uint32_t size)
{
	uint32_t		i;
	t_sym			tmp;

	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(syms[i].name, syms[i + 1].name) > 0)
		{
			tmp.value = syms[i].value;
			tmp.type = syms[i].type;
			tmp.name = syms[i].name;
			syms[i].value = syms[i + 1].value;
			syms[i].type = syms[i + 1].type;
			syms[i].name = syms[i + 1].name;
			syms[i + 1].value = tmp.value;
			syms[i + 1].type = tmp.type;
			syms[i + 1].name = tmp.name;
			i = -1;
		}
		i++;
	}
}

static void			print_sym(t_bin *bin)
{
	uint32_t		i;
	char			*strtable;
	struct nlist_64	*symtable;

	symtable = g_file + bin->symtab->symoff;
	strtable = g_file + bin->symtab->stroff;
	bin->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * bin->symtab->nsyms);
	i = 0;
	while (i < bin->symtab->nsyms)
	{
		bin->syms[i].type = get_symtype(symtable[i].n_type, symtable[i].n_sect, bin->sects);
		bin->syms[i].value = symtable[i].n_value;
		bin->syms[i].name = strtable + symtable[i].n_un.n_strx;
		i++;
	}
	free(bin->sects);
	sort_syms(bin->syms, bin->symtab->nsyms);
	i = 0;
	while (i < bin->symtab->nsyms)
	{
		if (bin->syms[i].type == 'u' || bin->syms[i].type == 'U')
		{
			printf("%18c %s\n", bin->syms[i].type, bin->syms[i].name);
		}
		else if (bin->syms[i].type)
			printf("%.16llx %c %s\n", bin->syms[i].value, bin->syms[i].type, bin->syms[i].name);
		i++;
	}
}

void				handle_64(t_bool swap)
{
	t_bin						bin;
	uint32_t					i;

	if (swap)
	{
		ft_putendl("SWAP");
		return ;
	}
	bin.header = (struct mach_header *)g_file;
	bin.lc = g_file + sizeof(struct mach_header_64);
	bin.nsects = 0;
	i = 0;
	while (i < bin.header->ncmds)
	{
		if (bin.lc->cmd == LC_SEGMENT_64)
		{
			count_sections_64(&bin);
		}
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	get_sections_64(&bin, g_file);
	i = 0;
	bin.lc = g_file + sizeof(struct mach_header_64);
	while (i < bin.header->ncmds)
	{
		if (bin.lc->cmd == LC_SYMTAB)
		{
			bin.symtab = (struct symtab_command *)bin.lc;
			print_sym(&bin);
			break ;
		}
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
}
