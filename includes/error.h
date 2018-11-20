/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:22:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/20 17:16:49 by ljoly            ###   ########.fr       */
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
}				t_err;

// typedef enum	e_usage
// {
// 	ARG,
// 	DIR,
//     FORMAT,
// }				t_usage;

void		err_cmd(const t_err err, const char *arg);

#endif