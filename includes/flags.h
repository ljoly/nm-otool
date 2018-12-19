/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:30:08 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 21:22:17 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# include "libft.h"

# define ONLY_UNDF 0x1
# define NO_UNDF 0x2
# define ONLY_NAMES 0x4
# define NO_SORT 0x8
# define ONLY_EXTERN 0x10

int				g_flags;

typedef struct	s_flag
{
	char		*name;
	int			code;
}				t_flag;

t_bool			handle_flags(int ac, char **av, int *n_arg);

t_bool			is_only_undf(void);
t_bool			is_no_undf(void);
t_bool			is_only_names(void);
t_bool			is_no_sort(void);
t_bool			is_only_extern(void);

#endif
