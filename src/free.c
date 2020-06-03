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

allocInfo	*concat_free(allocInfo *actual)
{
	allocInfo	*tmp;
	allocInfo	*tmp_next;

	tmp = actual;
	tmp_next = actual->next;
	while (tmp_next != NULL && tmp_next->isFree == 1)
	{
		actual->size += tmp_next->size;
		tmp_next = tmp_next->next;
	}
	actual->next = tmp_next;
	return (actual);
}

allocInfo	*split_free(allocInfo *actual, size_t size)
{
	allocInfo	*next;
	allocInfo	new;

	new.size = actual->size - (size + structSize);
	new.isFree = 1;
	new.next = actual->next;
	actual->isFree = 0;
	actual->size = size + structSize;
	actual->next = (void*)actual + size + structSize;
	ft_memcpy(actual->next, &new, structSize);
	return (actual);
}

allocInfo	*previous_zone(allocInfo *map, allocInfo *actual)
{
	allocInfo	*prev;

	prev = map;
	if (prev == actual)
		return (0);
	while (prev->next != NULL && prev->next != actual)
		prev = prev->next;
	return (prev);
}

void		free(void *ptr)
{
	allocInfo	*prev;
	allocInfo	*freed;

	if (ptr == NULL)
		exit(0);
	freed = ptr - structSize;
	if (exists(freed))
		exit(0);
	if (freed->size <= 4096)
		freed->isFree = 1;
	else
	{
		prev = previous_zone(PAGES.large, freed);
		if (prev)
			prev->next = freed->next;
		else
			PAGES.large = freed->next;
		munmap(freed, freed->size);
	}
}
