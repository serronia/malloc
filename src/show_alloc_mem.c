/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 18:10:10 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/07 18:10:23 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void show_alloc_mem()
{
    write(1, "Tiny : ", 8);
    print_addr(PAGES.tiny);
    write(1, "\n", 1);
    print_all(PAGES.tiny);
    write(1, "Small : ", 9);
    print_addr(PAGES.small);
    write(1, "\n", 1);
    print_all(PAGES.small);
    write(1, "Large : ", 9);
    print_addr(PAGES.large);
    write(1, "\n", 1);
    print_all(PAGES.large);
}

void print_all(allocInfo *map)
{
    while (map)
    {
        print_addr((void *)map);
        write(1, " - ", 3);
        print_addr((void *)map + map->size);
        write(1, " : ", 3);
        ft_putnbr(map->size);
        write(1, " octets\n", 8);
        if (map->next == NULL)
            return ;
        map = map->next;
    }
}

void print_addr(void *addr)
{
    size_t  base;
    size_t  diviseur;
    size_t  result;
    size_t  nbr;

    base = 16;
    nbr = (size_t)addr;
    diviseur = 1;
    while ((nbr / diviseur) >= base)
        diviseur = diviseur * base;
    write(1, "0x", 2);
    while (diviseur > 0)
    {
        result = (nbr / diviseur) % base ;
        if (result < 10)
            result +=48;
        else
            result += 97 - ((result/base) + 10);
        write(1, &result, 1);
        diviseur = diviseur / base;
    }
}
