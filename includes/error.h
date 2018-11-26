/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:22:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/26 14:22:07 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_err
{
	NO_ERR,
	ARG,
	DIR,
    FORMAT,
	OPEN,
    FSTAT,
	MMAP,
    MUNMAP,
	MALLOC,
}				t_err;

void		err_cmd(const t_err err, const char *arg);

#endif