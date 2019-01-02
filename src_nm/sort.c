/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ljoly <ljoly@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 12:12:13 by ljoly             #+#    #+#             */
/*   Updated: 2018/12/31 14:02:40 by ljoly            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

// static void		*insert(t_node **root, t_sym *sym)
// {
//     /* If the tree is empty, return a new Node */
//     if (node == NULL) return newNode(key); 
  
//     /* Otherwise, recur down the tree */
//     if (key < node->key) 
//         node->left  = insert(node->left, key); 
//     else if (key > node->key) 
//         node->right = insert(node->right, key); 
  
//     /* return the (unchanged) Node pointer */
//     return node;
// }

// void			sort_syms(t_sym *syms, uint32_t size)
// {
// 	uint32_t	i;

// 	insert(&root, &syms[0]);
// 	i = 1;
// 	while (i < size)
// 	{
// 		insert(&root, &syms[i]);
// 		i++;
// 	}
// }

static void		swap_syms(t_sym *sym1, t_sym *sym2)
{
	// t_sym		*sym2_prev;

	// tmp.value = sym1->value;
	// tmp.type = sym1->type;
	// tmp.name = sym1->name;
	// sym1->value = sym2->value;
	// sym1->type = sym2->type;
	// sym1->name = sym2->name;
	// sym2->value = tmp.value;
	// sym2->type = tmp.type;
	// sym2->name = tmp.name;

	// sym2_prev = sym2->prev;
	sym2->prev = sym1->prev;
	sym1->next = sym2->next;
	sym2->next = sym1;
	sym1->prev = sym2;
}

void			sort_syms(t_sym *syms, uint32_t size)
{
	t_sym		**tmp;
	t_sym		**tmp2;
	t_bool		sorted;
	uint32_t	i;
	int			cmp;

	size = 0;
	// ft_printf("size = %u\n", size);
	sorted = FALSE;
	while (!sorted)
	{
		sorted = TRUE;
		i = 0;
		tmp = &syms;
		while ((*tmp)->next)
		{
			// ft_printf("%u\n", i);
			tmp2 = &(*tmp)->next;
			cmp = ft_strcmp((*tmp)->name, (*tmp2)->name);
			if (cmp > 0)
			{
				// ft_printf("before: prev = %u next = %u\n", tmp->prev, tmp->next);
				swap_syms(*tmp, *tmp2);
				// ft_printf("after: prev = %u next = %u\n", tmp->prev, tmp->next);
				// exit(0);
				sorted = FALSE;
			}
			else if (cmp == 0 && (*tmp)->value > (*tmp2)->value)
			{
				swap_syms(*tmp, *tmp2);
				sorted = FALSE;
			}
			*tmp = (*tmp)->next;
			i++;
			if (sorted)
			{
				ft_printf("i = %u\n", i);
			}
		}
	}
}
