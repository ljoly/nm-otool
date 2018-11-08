/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/08 19:54:44 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

# include "libft.h"
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <sys/stat.h>

typedef struct	s_sym
{
	uint64_t	value;
	uint8_t		type;
	char		*name;
}				t_sym;

typedef struct	s_env
{
	char		*p;
	t_sym		*symtab;
	int			exit_status;
}				t_env;

# define SWAP 1
# define NOSWAP 0

typedef struct	s_magic
{
	unsigned int	num;
	t_bool			swap;
	void			(*cmd)(char *p, t_bool swap);
}				t_magic;

void			handle_arg(t_env *e, char *arg, int *fd);
void			handle_magic(t_env *e, char *arg);
void			handle_64(char *p, t_bool swap);

#endif