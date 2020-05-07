/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memccpy.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:52:54 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:52:54 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*t;
	unsigned char	*f;
	unsigned char	c_cpy;
	size_t			i;

	i = 0;
	c_cpy = (unsigned char)c;
	t = (unsigned char *)dst;
	f = (unsigned char *)src;
	while (i < n)
	{
		*t = *f;
		if (*f == c_cpy)
			return ((unsigned char *)dst + i + 1);
		i++;
		t++;
		f++;
	}
	return (NULL);
}
