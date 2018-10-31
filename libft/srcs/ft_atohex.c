/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atohex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 17:19:24 by ljoly             #+#    #+#             */
/*   Updated: 2018/07/12 16:50:49 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		fill_dst(char **dst, char *tab, size_t nb)
{
	while (**dst != '\0')
		(*dst)++;
	**dst = tab[nb / 16];
	(*dst)++;
	**dst = tab[nb % 16];
}

char			*ft_atohex(const char *src, int upper)
{
	char		*tab;
	char		*ret;
	char		*tmp;
	size_t		len;
	size_t		i;

	ret = NULL;
	len = ft_strlen(src);
	if (!(ret = (char *)ft_memalloc(sizeof(char) * 2 * len + 1)))
		return (NULL);
	tab = (upper == 1) ? HEX_UP : HEX;
	i = 0;
	tmp = ret;
	while (i < len)
	{
		fill_dst(&tmp, tab, (int)src[i]);
		i++;
	}
	return (ret);
}
