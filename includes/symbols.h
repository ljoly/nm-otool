/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbols.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:35:50 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/14 16:51:56 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYMBOLS_H
# define SYMBOLS_H

# include <stdint.h>

typedef struct	s_sym
{
	uint64_t	value;
	uint8_t		type;
	char		*name;
}				t_sym;

#endif