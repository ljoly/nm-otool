/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:35:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/12 19:37:18 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_MAGIC_H
# define HANDLE_MAGIC_H

# include "libft.h"

# define SWAP 1
# define NOSWAP 0

typedef struct	s_magic
{
	unsigned int	num;
	t_bool			swap;
	void			(*cmd)(char *p, t_bool swap);
}				t_magic;

void			handle_magic(char *bin, char *arg);

#endif