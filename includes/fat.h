/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:00:22 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/03 14:21:49 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FAT_H
# define FAT_H

typedef struct	s_fat
{
	struct fat_header	*header;
	struct fat_arch		*arch;
	t_file				mach_o;
	int					magic;
}				t_fat;

#endif
