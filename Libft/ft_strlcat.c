/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:53:00 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:53:00 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	char	*dest;
	char	*source;
	size_t	i;
	size_t	j;

	i = 0;
	dest = dst;
	source = (char *)src;
	while (i++ < size && *dest)
		dest++;
	j = dest - dst;
	i = size - j;
	if (i == 0)
		return (j + ft_strlen(source));
	while (*source)
	{
		if (i != 1)
		{
			*dest++ = *source;
			i--;
		}
		source++;
	}
	*dest = '\0';
	return (j + (source - src));
}
