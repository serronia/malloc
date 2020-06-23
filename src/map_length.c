#include "ft_malloc.h"

int			map_length(t_allocinfo *map, int pages, size_t size)
{
	size_t	total_length;

	total_length = map->size;
	if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
		return (0);
	while (map->next != NULL)
	{
		map = map->next;
		total_length += map->size;
		if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
			return (0);
	}
	total_length -= (total_length / (pages * getpagesize()))
			* (pages * getpagesize());
	if ((total_length + size + STRUCTSIZE + 1) > (pages * getpagesize()))
		map->next = (t_allocinfo *)call_mmap(map, pages, size);
	return (0);
}

t_allocinfo	*map_length_large(t_allocinfo *map, int pages, size_t size)
{
	size_t	total_len;

	total_len = map->size;
	total_len > 32768 ? total_len = 0 : 0;
	if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
		return (NULL);
	while (map->next != NULL)
	{
		map = map->next;
		total_len = total_len + map->size > 32768 ? 0 : total_len + map->size;
		if (map->is_free == 1 && map->size >= size + STRUCTSIZE)
			return (NULL);
	}
	if (size + STRUCTSIZE > 32768 - total_len)
	{
		map->next = mmap(NULL, (getpagesize() * ((size + STRUCTSIZE) /\
					getpagesize() + 8)), PROT_READ | PROT_WRITE,
					MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
		map = map->next;
		map->next = NULL;
		map->size = size + 16;
		map->is_free = 0;
		return (map);
	}
	return (NULL);
}
