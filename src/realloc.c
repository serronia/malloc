/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:10:02 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/07 18:10:03 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void *realloc(void *ptr, size_t size)
{
    allocInfo *zone;
    allocInfo *actual;

    zone = ptr - 16;
    if (zone->size >= size + 16 * 2)
        zone = splitZone(zone, size);
    else
    {
        actual = zone;
        zone = malloc(size);
        ft_memcpy(zone, actual, actual->size);
        actual->isFree = 1;

    }
    return ((void*)zone + (sizeof(allocInfo)));
}

allocInfo *splitZone(allocInfo *actual, size_t size)
{
    allocInfo new;

    new.size = actual->size - (size + structSize);
    new.next = actual->next;
    new.isFree = 1;
    actual->size = size + structSize;
    actual->next = (void*)actual + actual->size;
    ft_memcpy(actual->next, &new, structSize);
    return (actual);
}
