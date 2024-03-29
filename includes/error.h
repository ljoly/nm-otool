/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 14:22:25 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/19 17:57:54 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

typedef enum	e_err
{
	NO_ERR,
	DIR,
	FORMAT,
	OPEN,
	FSTAT,
	MMAP,
	MUNMAP,
	MALLOC,
	FLAG_DUP,
	NOT_A_FLAG
}				t_err;

void		err_cmd(const t_err err, const char *arg);

#endif
