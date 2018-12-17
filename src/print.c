/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 18:29:53 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/17 02:35:50 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void		fill_dst_num(char **dst, char *tab, size_t nb)
{
	while (nb / 16 >= 16)
	{
		ft_putendl("IN");
		ft_printf("nb = %zu\n", nb);
		**dst = tab[nb % 16];
		nb /= 16;
		(*dst)--;
		if (nb / 16 >= 16)
			ft_putendl("OUT");
	}
	**dst = tab[nb];
	ft_putchar(**dst);
}

static void		fill_dst(char **dst, char *tab, int nb)
{
	while (**dst != '\0')
		(*dst)++;
	**dst = tab[nb / 16];
	(*dst)++;
	**dst = tab[nb % 16];
}

static char			*ft_atohexi(const char *src, size_t nb, int upper)
{
	char		*tab;
	char		*ret;
	char		*tmp;
	size_t		len;
	size_t		i;

	ret = NULL;
	len = src ? ft_strlen(src) * 2 : ft_hex_size(nb);
	if (!(ret = (char *)ft_memalloc(sizeof(char) * len + 1)))
		return (NULL);
	tab = (upper == 1) ? HEX_UP : HEX;
	i = 0;
	tmp = ret;
	if (src)
	{
		while (i < len)
		{
			fill_dst(&tmp, tab, (int)src[i]);
			i++;
		}
	}
	else
	{
		tmp = ret + len - 1;
		fill_dst_num(&tmp, tab, nb);
	}
	return (ret);
}



char			buff[512];

static void		fill_zeros(uint32_t size)
{
	uint32_t	i;

	i = 0;
	while(i < size)
	{
		buff[i] = '0';
		i++;
	}
}

static void		fill_blank(uint32_t size)
{
	uint32_t	i;

	i = 0;
	while (i < size)
	{
		buff[i] = ' ';
		i++;
	}
}

static void		print_syms32(const t_mach o)
{
	uint32_t	i;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' || o.syms[i].type == 'U' ||
			o.syms[i].type == 'i' || o.syms[i].type == 'I')
		{
			ft_printf("%10c %s\n", o.syms[i].type, o.syms[i].name);
		}
		else if (o.syms[i].type)
		{
			ft_printf("%.8llx %c %s\n", o.syms[i].value, o.syms[i].type,
				o.syms[i].name);
		}
		i++;
	}
}

static void		print_syms64(const t_mach o)
{
	uint32_t	i;
	uint32_t	len;
	// char		*tmp;
	char		*hex;

	i = 0;
	while (i < o.symtab->nsyms)
	{
		if (o.syms[i].type == 'u' || o.syms[i].type == 'U' ||
			o.syms[i].type == 'i' || o.syms[i].type == 'I')
		{
			fill_blank(17);
			buff[17] = o.syms[i].type;
			buff[18] = ' ';
		}
		else if (o.syms[i].type)
		{
			ft_printf("value = %u\n", o.syms[i].value);
			// tmp = ft_itoa(o.syms[i].value);
			// ft_putendl(tmp);
			hex = ft_atohexi(NULL, o.syms[i].value, FALSE);
			ft_putendl(hex);
			exit(0);
			// free(tmp);
			len = ft_strlen(hex);
			fill_zeros(16 - len);
			ft_strcpy(&buff[16 - len], hex); 

		}
		ft_strcpy(&buff[19], o.syms[i].name);
		len = ft_strlen(o.syms[i].name);
		buff[19 + len] = '\n';
		ft_putstr(buff);
		i++;
	}
}

void	print_syms(const t_mach o, t_bool arch_64)
{
	// ft_bzero(buff, 512);
	if (arch_64)
	{
		print_syms64(o);
	}
	else
	{
		print_syms32(o);
	}
}
