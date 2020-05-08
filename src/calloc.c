/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 00:17:19 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/09 00:17:21 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void *calloc(size_t nbElement, size_t sizeElement)
{
    size_t totalSize;
    void *ptr;
    allocInfo *zone;

    totalSize = nbElement * sizeElement;
    if ((ptr = malloc(totalSize)) == NULL)
        return (NULL);
    zone = ptr + structSize;
    zone = ft_memset(zone, 0, sizeElement);
    return (ptr);
}