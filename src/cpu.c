/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpu.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:59:35 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/12 19:35:10 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fat.h"

t_cpu		g_cpu32[4] = {
	{CPU_TYPE_X86, "x86"},
	{CPU_TYPE_I386, "i386"},
	{CPU_TYPE_ARM, "arm"},
	{CPU_TYPE_POWERPC, "ppc"}
};

t_bool		is_cpu_64(const int type)
{
	return (type == CPU_TYPE_X86_64 || type == CPU_TYPE_ARM64 ||
		type == CPU_TYPE_POWERPC64);
}
