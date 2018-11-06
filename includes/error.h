/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:22:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/05 17:42:14 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_sys
{
	OPEN,
    FSTAT,
	MMAP,
    MUNMAP,
}				t_sys;

typedef enum	e_usage
{
	ARG,
    MAGIC,
}				t_usage;

void		err_sys(t_env *e, t_sys err_code, const char *arg);
void		err_usage(t_usage err_code);

#endif