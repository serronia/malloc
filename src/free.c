#include "ft_malloc.h"

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
	pthread_mutex_lock(&g_mutex);
	if (exists(freed))
	{
		pthread_mutex_unlock(&g_mutex);
		return ;
	}
	pthread_mutex_unlock(&g_mutex);
	freed->is_free = 1;
}
