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
	t_allocinfo	*zone;

	if (g_pages.tiny == NULL)
	{
		g_pages.tiny = (t_allocinfo *)call_mmap(g_pages.tiny, 4, size);
		zone = g_pages.tiny;
	}
	else
	{
		map_length(g_pages.tiny, 4, size);
		zone = next_zone(g_pages.tiny, size);
	}
	return ((void*)zone + sizeof(t_allocinfo));
}

void	*small(size_t size)
{
	t_allocinfo	*zone;

	if (g_pages.small == NULL)
	{
		g_pages.small = (t_allocinfo *)call_mmap(g_pages.small, 26, size);
		zone = g_pages.small;
	}
	else
	{
		map_length(g_pages.small, 26, size);
		zone = next_zone(g_pages.small, size);
	}
	return ((void*)zone + sizeof(t_allocinfo));
}

void	*large(size_t size)
{
	t_allocinfo	*zone;
	size_t		nb_page;

	nb_page = ((size + STRUCTSIZE) / getpagesize() + 8);
	if (g_pages.large == NULL)
	{
		g_pages.large = (t_allocinfo *)call_mmap(g_pages.large, nb_page, size);
		zone = g_pages.large;
	}
	else
	{
		if ((zone = map_length_large(g_pages.large, 1, size)) == NULL)
		{
			zone = next_zone(g_pages.large, size);
		}
	}
	return ((void*)zone + sizeof(t_allocinfo));
}

void	*malloc(size_t size)
{
	void	*allocation;

	size = align_number(size);
	allocation = NULL;
	if (size <= 0)
		return (allocation);
	if (STRUCTSIZE + size <= TS)
		allocation = tiny(size);
	else if (STRUCTSIZE + size <= SS)
		allocation = small(size);
	else
		allocation = large(size);
	return (allocation);
}
