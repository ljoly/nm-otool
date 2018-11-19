/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/19 20:11:28 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static uint8_t		get_type(uint8_t n_type, uint8_t n_sect, t_sect *sects)
{
	uint8_t			t;

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
	// else if (t ==  N_INDR)
	// {
// 
	// }
	if (n_type & N_EXT)
	{
		t -= 32;
	}
	return (t);
}

t_bool				print_sym64(t_bin *bin)
{
	uint32_t		i;
	char			*strtable;
	struct nlist_64	*arr;

	arr = g_file + bin->symtab->symoff;
	strtable = g_file + bin->symtab->stroff;
	if (!access_at(&arr[bin->symtab->nsyms - 1].n_value) ||
		!access_at((void*)(strtable + arr[bin->symtab->nsyms - 1].n_un.n_strx)))
		return (FALSE);
	bin->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * bin->symtab->nsyms);
	i = -1;
	while (++i < bin->symtab->nsyms)
	{
		bin->syms[i].type = get_type(arr[i].n_type, arr[i].n_sect, bin->sects);
		bin->syms[i].value = arr[i].n_value;
		bin->syms[i].name = strtable + arr[i].n_un.n_strx;
	}
	free(bin->sects);
	sort_syms(bin->syms, bin->symtab->nsyms);
	i = -1;
	while (++i < bin->symtab->nsyms)
	{
		if (bin->syms[i].type == 'u' || bin->syms[i].type == 'U')
			printf("%18c %s\n", bin->syms[i].type, bin->syms[i].name);
		else if (bin->syms[i].type)
			printf("%.16llx %c %s\n", bin->syms[i].value, bin->syms[i].type,
				bin->syms[i].name);
	}
	return (TRUE);
}

t_bool				get_syms(t_bin bin, t_bool (*print_sym)(t_bin *bin))
{
	uint32_t		i;

	i = 0;
	while (i < bin.header->ncmds)
	{
		if (!access_at((void*)bin.lc + bin.lc->cmdsize))
			return (FALSE);
		if (bin.lc->cmd == LC_SYMTAB)
		{
			bin.symtab = (struct symtab_command *)bin.lc;
			return (print_sym(&bin));
		}
		bin.lc = (void *)bin.lc + bin.lc->cmdsize;
		i++;
	}
	return (FALSE);
}
