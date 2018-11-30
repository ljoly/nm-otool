/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:35:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/30 17:09:25 by ljoly            ###   ########.fr       */
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
	t_bool			(*cmd)(t_file f, const char *arg);
}				t_magic;

void			handle_magic(const int magic, t_file f, const char *arg);

#endif