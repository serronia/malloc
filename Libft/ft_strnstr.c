/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnstr.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:53:02 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:53:02 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)&haystack[i]);
	while (needle[j] != '\0')
		j++;
	while (haystack[i] != '\0' && i < len)
	{
		if (len < ft_strlen((char *)needle))
			return (NULL);
		k = 0;
		while (haystack[i] == needle[k] && haystack[i] != '\0' && i < len)
		{
			i++;
			k++;
		}
		if (k == j)
			return ((char *)&haystack[i - k]);
		i = i - k + 1;
	}
	return (NULL);
}
