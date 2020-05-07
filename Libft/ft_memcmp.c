/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcmp.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:52:55 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:52:55 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*t;
	unsigned char	*s;
	size_t			i;

	i = 0;
	t = (unsigned char *)s1;
	s = (unsigned char *)s2;
	while (i < n)
	{
		if (t[i] != s[i])
			return (t[i] - s[i]);
		i++;
	}
	return (0);
}
