#include "ft_malloc.h"

void	*calloc(size_t nb_element, size_t size_element)
{
	void		*ptr;
	t_allocinfo	*zone;
	size_t		total_size;

	total_size = nb_element * size_element;
	if ((ptr = malloc(total_size)) == NULL)
		return (NULL);
	zone = ptr + TS;
	zone = ft_memset(zone, 0, size_element);
	return (ptr);
}
