/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/27 18:54:57 by ljoly            ###   ########.fr       */
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
	char			*strtable;
	struct nlist_64	*arr;

	arr = f.ptr + bin->symtab->symoff;
	strtable = f.ptr + bin->symtab->stroff;
	i = 0;
	ft_printf("nsects = %u\nnsyms = %u\n", bin->nsects, bin->symtab->nsyms);
	while (i < bin->symtab->nsyms)
	{
		ft_putendl("IN");

		if (!access_at(f, &arr[i].n_value))
			return (FALSE);
		ft_putendl("ACCESS_1");
		if (!access_at(f, &arr[i].n_un.n_strx))
			return (FALSE);
		ft_putendl("ACCESS_2");		
		if (!access_at(f, (void*)(strtable + arr[i].n_un.n_strx)))
			return (FALSE);
		ft_putendl("ACCESS_3");
		// if (!access_at(f, &arr[i].n_value) ||
			// !access_at(f, (void*)(strtable + arr[i].n_un.n_strx)))
			// return (FALSE);
		// ft_printf("ptr = %p && n_value = %u\n", &arr[i].n_value, arr[i].n_value);
		bin->syms[i].type = get_type(arr[i].n_type, arr[i].n_sect,
			arr[i].n_value, bin->sects);
		ft_putendl("1");

		bin->syms[i].value = arr[i].n_value;
		ft_putendl("2");

		bin->syms[i].name = strtable + arr[i].n_un.n_strx;
		ft_putendl("OUT");
		i++;
	}
	ft_putendl("OUT OF LOOP");
	return (TRUE);
}

static t_bool		get_symtab(const char *arg, t_bin *bin)
{
	bin->symtab = (struct symtab_command *)bin->lc;

	// CHECK nsyms HERE

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
		if (!access_at(f, (void*)bin->lc + bin->lc->cmdsize))
			return (free_memory(bin->sects, NULL, FALSE));
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
