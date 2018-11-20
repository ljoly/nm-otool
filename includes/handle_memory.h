/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_memory.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 16:20:19 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/20 18:00:34 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLE_MEMORY_H
# define HANDLE_MEMORY_H

# include "ft_nm.h"

# define ALL 0x0
# define SECTIONS 0x1
# define SYMBOLS 0x2

t_bool		free_memory(t_sect *sects, t_sym *syms, t_bool status);

#endif