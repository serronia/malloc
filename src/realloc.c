#include "ft_malloc.h"

void		*realloc(void *ptr, size_t size)
{
	t_allocinfo	*zone;
	t_allocinfo	*next;
	t_allocinfo	*next_tmp;
	size_t		tmp_size;

	zone = ptr - STRUCTSIZE;
	if (exists(zone))
		return (NULL);
	if (zone->size >= size + STRUCTSIZE * 2)
		zone = split_zone(zone, size);
	else
	{
		next = (void *)malloc(size) - 16;
		next_tmp = next->next;
		tmp_size = next->size;
		ft_memcpy(next, zone, zone->size - 16);
		next->size = tmp_size;
		next->next = next_tmp;
		zone->is_free = 1;
		zone = next;
	}
	return ((void*)zone + 16);
}

t_allocinfo	*split_zone(t_allocinfo *actual, size_t size)
{
	t_allocinfo	new;

	new.size = actual->size - (size + STRUCTSIZE);
	new.next = actual->next;
	new.is_free = 1;
	actual->size = size + STRUCTSIZE;
	actual->next = (void*)actual + actual->size;
	ft_memcpy(actual->next, &new, STRUCTSIZE);
	return (actual);
}

int			exists(t_allocinfo *map)
{
	t_allocinfo *reel;

	reel = g_pages.tiny;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = g_pages.small;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	reel = g_pages.large;
	while (reel != NULL)
	{
		if (reel == map)
			return (0);
		reel = reel->next;
	}
	return (1);
}
