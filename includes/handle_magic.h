/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_magic.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 19:35:27 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/20 15:56:30 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_MAGIC_H
# define HANDLE_MAGIC_H

# include "libft.h"
# include <ar.h>

# define SWAP 1
# define NOSWAP 0

# define AR_MAGIC 0xa3e686372613c21
# define AR_MAG 0xa3e6863

typedef struct	s_magic
{
	int				num;
	t_bool			swp;
	t_bool			(*cmd)(t_file f, const char *arg);
}				t_magic;

t_bool			handle_magic(int magic, t_file f, const char *arg);
t_bool			handle_magic_otool(int magic, t_file f, const char *arg, t_bool
	print);

#endif
