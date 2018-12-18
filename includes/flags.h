/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 14:30:08 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/18 18:50:59 by ljoly            ###   ########.fr       */
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

int			g_flags;

t_bool		get_flags(int ac, char **av);

#endif