/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:01:51 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/04 16:39:22 by ljoly            ###   ########.fr       */
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
	if (t == N_UNDF && n_value)
	{
		t = 'c';
	}
	else if ((t == N_UNDF && !n_value) || t == N_PBUD)
	{
		t = 'u';
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
		t = 'i';
	}
	else
	{
		t = '?';
	}
	if (n_type & N_EXT)
	{
		t -= 32;
	}
	return (t);
}

t_bool				get_syms_64(t_file f, t_mach *o)
{
	uint32_t		i;
	struct nlist_64	*table;
	char			*strtable;

	table = f.ptr + o->symtab->symoff;
	strtable = f.ptr + o->symtab->stroff;
	i = 0;
	while (i < o->symtab->nsyms)
	{
		o->syms[i].type = get_type(table[i].n_type, table[i].n_sect,
			table[i].n_value, o->sects);
		o->syms[i].value = table[i].n_value;
		o->syms[i].name = strtable + table[i].n_un.n_strx;
		i++;
	}
	return (TRUE);
}

static t_bool		get_symtab(const char *arg, t_mach *o)
{
	o->symtab = (struct symtab_command *)o->lc;
	if (!(o->syms = (t_sym*)ft_memalloc(sizeof(t_sym) * o->symtab->nsyms)))
	{
		err_cmd(MALLOC, arg);
		return (FALSE);
	}
	return (TRUE);
}

t_bool				handle_syms(t_file f, const char *arg, t_mach *o,
	t_bool (*get_syms)(t_file f, t_mach *o))
{
	uint32_t		i;

	i = 0;
	while (i < o->header->ncmds)
	{
		if (o->lc->cmd == LC_SYMTAB)
		{
			if (!get_symtab(arg, o))
			{
				return (free_memory(o->sects, o->syms, FALSE));
			}
			if (!get_syms(f, o))
			{
				return (free_memory(o->sects, o->syms, FALSE));
			}
		}
		o->lc = (void *)o->lc + o->lc->cmdsize;
		i++;
	}
	free(o->sects);
	sort_syms(o->syms, o->symtab->nsyms);
	print_syms(*o);
	return (free_memory(NULL, o->syms, TRUE));
}
