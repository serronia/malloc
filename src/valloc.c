#include "ft_malloc.h"

void	*valloc(size_t size)
{
	return (malloc(getpagesize() * nb_pages(size)));
}
