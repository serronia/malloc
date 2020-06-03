/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:38:47 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:38:52 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	*calloc(size_t nb_element, size_t size_element)
{
	void		*ptr;
	allocInfo	*zone;
	size_t		total_size;

	total_size = nb_element * size_element;
	if ((ptr = malloc(total_size)) == NULL)
		return (NULL);
	zone = ptr + structSize;
	zone = ft_memset(zone, 0, size_element);
	return (ptr);
}
