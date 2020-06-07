/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:01 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:02 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

t_allocinfo	*concat_free(t_allocinfo *actual)
{
	t_allocinfo	*tmp;
	t_allocinfo	*tmp_next;

	tmp = actual;
	tmp_next = actual->next;
	while (tmp_next != NULL && tmp_next->is_free == 1)
	{
		actual->size += tmp_next->size;
		tmp_next = tmp_next->next;
	}
	actual->next = tmp_next;
	return (actual);
}

t_allocinfo	*split_free(t_allocinfo *actual, size_t size)
{
	t_allocinfo	*next;
	t_allocinfo	new;

	new.size = actual->size - (size + STRUCTSIZE);
	new.is_free = 1;
	new.next = actual->next;
	actual->is_free = 0;
	actual->size = size + STRUCTSIZE;
	actual->next = (void*)actual + size + STRUCTSIZE;
	ft_memcpy(actual->next, &new, STRUCTSIZE);
	return (actual);
}

t_allocinfo	*previous_zone(t_allocinfo *map, t_allocinfo *actual)
{
	t_allocinfo	*prev;

	prev = map;
	if (prev == actual)
		return (0);
	while (prev->next != NULL && prev->next != actual)
		prev = prev->next;
	return (prev);
}

void		free(void *ptr)
{
	t_allocinfo	*prev;
	t_allocinfo	*freed;

	if (ptr == NULL)
		return ;
	freed = ptr - STRUCTSIZE;
	if (exists(freed))
		return ;
	//if (freed->size <= 4096)
		freed->is_free = 1;
//	else
//	{
//		prev = previous_zone(g_pages.large, freed);
//		if (prev)
//			prev->next = freed->next;
//		else
//			g_pages.large = freed->next;
//		munmap(freed, freed->size);
//	}
}
