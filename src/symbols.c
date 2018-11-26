/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/26 18:04:59 by ljoly            ###   ########.fr       */
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

t_bool				get_syms64(t_bin *bin)
{
	uint32_t		i;
	char			*strtable;
	struct nlist_64	*arr;

	arr = g_file + bin->symtab->symoff;
	strtable = g_file + bin->symtab->stroff;
	i = 0;
	while (i < bin->symtab->nsyms)
	{
		if (!access_at(&arr[i].n_value) ||
			!access_at((void*)(strtable + arr[i].n_un.n_strx)))
			return (FALSE);
		bin->syms[i].type = get_type(arr[i].n_type, arr[i].n_sect,
			arr[i].n_value, bin->sects);
		bin->syms[i].value = arr[i].n_value;
		bin->syms[i].name = strtable + arr[i].n_un.n_strx;
		i++;
	}
	return (TRUE);
}

static t_bool		get_symtab(t_bin *bin)
{
	bin->symtab = (struct symtab_command *)bin->lc;
	if (!(bin->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * bin->symtab->nsyms)))
	{
		err_cmd(MALLOC, "system");
		return (FALSE);
	}
	return (TRUE);
}

t_bool				handle_syms(t_bin *bin, t_bool (*get_syms)(t_bin *bin))
{
	uint32_t		i;

	i = 0;
	while (i < bin->header->ncmds)
	{
		if (!access_at((void*)bin->lc + bin->lc->cmdsize))
			return (free_memory(bin->sects, NULL, FALSE));
		if (bin->lc->cmd == LC_SYMTAB)
		{
			if (!get_symtab(bin))
			{
				return (free_memory(bin->sects, bin->syms, FALSE));
			}
			if (!get_syms(bin))
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
