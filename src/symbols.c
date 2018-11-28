/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/28 19:53:50 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "handle_memory.h"
#include "error.h"

static uint8_t		get_type(uint8_t n_type, uint8_t n_sect, uint64_t n_value,
	t_sect *sects)
{
	uint8_t			t;

	if (n_type & N_STAB)
	{
		return (FALSE);
	}
	t = n_type & N_TYPE;
	if (t == N_UNDF)
	{
		t = n_value ? 'c' : 'u';
	}
	else if (t == N_ABS)
	{
		t = 'a';
	}
	else if (t == N_SECT)
	{
		t = sects[n_sect - 1].symbol ? sects[n_sect - 1].symbol : 's';
	}
	else if (t ==  N_INDR)
	{
		t = '?';
	}
	if (n_type & N_EXT)
	{
		t -= 32;
	}
	return (t);
}

t_bool				get_syms64(t_file f, t_bin *bin)
{
	uint32_t		i;
	struct nlist_64	*table;
	char			*strtable;

	table = f.ptr + bin->symtab->symoff;
	strtable = f.ptr + bin->symtab->stroff;
	i = 0;
	while (i < bin->symtab->nsyms)
	{
		bin->syms[i].type = get_type(table[i].n_type, table[i].n_sect,
			table[i].n_value, bin->sects);
		bin->syms[i].value = table[i].n_value;
		bin->syms[i].name = strtable + table[i].n_un.n_strx;
		i++;
	}
	return (TRUE);
}

static t_bool		get_symtab(const char *arg, t_bin *bin)
{
	bin->symtab = (struct symtab_command *)bin->lc;
	if (!(bin->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * bin->symtab->nsyms)))
	{
		err_cmd(MALLOC, arg);
		return (FALSE);
	}
	return (TRUE);
}

t_bool				handle_syms(t_file f, const char *arg, t_bin *bin,
	t_bool (*get_syms)(t_file f, t_bin *bin))
{
	uint32_t		i;

	i = 0;
	while (i < bin->header->ncmds)
	{
		if (bin->lc->cmd == LC_SYMTAB)
		{
			if (!get_symtab(arg, bin))
			{
				return (free_memory(bin->sects, bin->syms, FALSE));
			}
			if (!get_syms(f, bin))
			{
				return (free_memory(bin->sects, bin->syms, FALSE));
			}
		}
		bin->lc = (void *)bin->lc + bin->lc->cmdsize;
		i++;
	}
	free(bin->sects);
	sort_syms(bin->syms, bin->symtab->nsyms);
	print_syms(*bin);
	return (free_memory(NULL, bin->syms, TRUE));
}
