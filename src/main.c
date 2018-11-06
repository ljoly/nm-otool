/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/30 14:31:10 by ljoly             #+#    #+#             */
/*   Updated: 2018/11/05 17:48:15 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"
#include "error.h"

void			print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int				i;
	char			*stringtable;
	struct nlist_64	*array;

	array = ptr + symoff;
	stringtable = ptr + stroff;
	i = 0;
	while (i < nsyms)
	{
		printf("%s\n", stringtable + array[i].n_un.n_strx);
		i++;
	}
}

void			handle_64(char *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;
	
	header = (struct mach_header_64 *)ptr;
	ncmds = header->ncmds;
	lc = (void *)ptr + sizeof(*header);
	i = 0;
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command *)lc;
			printf("nm symbols = %d\n", sym->nsyms);
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break;
		}
		lc = (void *)lc + lc->cmdsize;
		i++;
	}
}

void			ft_nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64)
	{
		handle_64(ptr);
	}
	else
	{
		printf("not a 64bits: magic number = %u\n", magic_number);
	}
}

int				main(int ac, char **av)
{
	int			i;
	t_env		e;
    int			fd;
    char		*ptr;
	struct stat	buf;

    if (ac < 2)
    {
		err_usage(ARG);
        return (EXIT_FAILURE);
    }
	i = 1;
	while (i < ac)
	{
		// debug only: print at the end of the program
		// if (ac > 2)
		// {
		// 	ft_printf("\n%s: \n", av[i]);
		// }
		//
		if ((fd = open(av[i], O_RDONLY)) < 0)
		{
			err_sys(&e, OPEN, av[i]);
		}
		if (fstat(fd, &buf) < 0)
		{
			err_sys(&e, FSTAT, av[i]);
		}
		if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		{
			ft_putendl_fd("mmap error", STDERR);
			return (EXIT_FAILURE);
		}
		ft_nm(ptr);
		if (munmap(ptr, buf.st_size) < 0)
		{
			ft_putendl_fd("munmap error", STDERR);
			return (EXIT_FAILURE);
		}
		printf("FD = %d\n", fd);
		close(fd);
		i++;
	}
    return (e.exit_status);
}