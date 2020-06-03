/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:09 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:10 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	*tiny(size_t size)
{
	allocInfo	*zone;

	if (PAGES.tiny == NULL)
	{
		PAGES.tiny = (allocInfo *)call_mmap(PAGES.tiny, 4, size);
		zone = PAGES.tiny;
	}
	else
	{
		map_length(PAGES.tiny, 4, size);
		zone = next_zone(PAGES.tiny, size);
	}
	return ((void*)zone + sizeof(allocInfo));
}

void	*small(size_t size)
{
	allocInfo	*zone;

	if (PAGES.small == NULL)
	{
		PAGES.small = (allocInfo *)call_mmap(PAGES.small, 26, size);
		zone = PAGES.small;
	}
	else
	{
		map_length(PAGES.small, 26, size);
		zone = next_zone(PAGES.small, size);
	}
	return ((void*)zone + sizeof(allocInfo));
}

void	*large(size_t size)
{
	size_t		nb_page;
	allocInfo	*zone;
	allocInfo	*map;

	map = PAGES.large;
	nb_page = ((size + structSize) / getpagesize()) + 1;
	if (PAGES.large == NULL)
	{
		PAGES.large = (allocInfo *)call_mmap(PAGES.large, nb_page, size);
		zone = PAGES.large;
	}
	else
	{
		zone = PAGES.large;
		while (zone->next != NULL)
			zone = zone->next;
		if (zone->next == NULL)
		{
			zone->next = (allocInfo *)call_mmap(PAGES.large, nb_page, size);
			zone = zone->next;
		}
	}
	return ((void*)zone + sizeof(allocInfo));
}

void	*malloc(size_t size)
{
	void	*allocation;

	size = align_number(size);
	allocation = NULL;
	if (size <= 0)
		return (allocation);
	if (structSize + size <= ts)
		allocation = tiny(size);
	else if (structSize + size <= ss)
		allocation = small(size);
	else
		allocation = large(size);
	return (allocation);
}
