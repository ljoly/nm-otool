/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:22:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/05 15:42:00 by ljoly            ###   ########.fr       */
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
    MAGIC,
}				t_usage;

int			err_sys(t_sys err_code, const char *arg);
int			err_usage(t_usage err_code);

#endif