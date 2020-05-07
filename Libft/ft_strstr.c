/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strstr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:53:02 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:53:02 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	if (haystack[0] == '\0' && needle[0] == '\0')
		return ((char *)&haystack[i]);
	while (needle[j] != '\0')
		j++;
	while (haystack[i] != '\0')
	{
		k = 0;
		while (haystack[i] == needle[k] && haystack[i] != '\0')
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
