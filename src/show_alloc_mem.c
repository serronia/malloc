/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdarko <jdarko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 16:39:29 by jdarko            #+#    #+#             */
/*   Updated: 2020/05/10 16:39:30 by jdarko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_malloc.h"

void	show_alloc_mem(void)
{
	write(1, "Tiny : ", 8);
	print_addr(g_pages.tiny);
	write(1, "\n", 1);
	print_all(g_pages.tiny);
	write(1, "Small : ", 9);
	print_addr(g_pages.small);
	write(1, "\n", 1);
	print_all(g_pages.small);
	write(1, "Large : ", 9);
	print_addr(g_pages.large);
	write(1, "\n", 1);
	print_all(g_pages.large);
}

void	print_all(t_allocinfo *map)
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
			break ;
		map = map->next;
	}
}

void	print_addr(void *addr)
{
	size_t	base;
	size_t	diviseur;
	size_t	result;
	size_t	nbr;

	base = 16;
	nbr = (size_t)addr;
	diviseur = 1;
	while ((nbr / diviseur) >= base)
		diviseur = diviseur * base;
	write(1, "0x", 2);
	while (diviseur > 0)
	{
		result = (nbr / diviseur) % base;
		if (result < 10)
			result += 48;
		else
			result += 97 - ((result / base) + 10);
		write(1, &result, 1);
		diviseur = diviseur / base;
	}
}
