/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strtrim.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:53:03 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:53:03 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	*ft_strtrim(char const *s)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	k = ft_strlen(s);
	while ((s[i] == 9 || s[i] == 10 || s[i] == 44 || s[i] == 32) && s[i] != 0)
		i++;
	if (i == k)
		return (ft_strdup(""));
	while ((s[k] == 9 || s[k] == 10 || s[k] == 44 || s[k] == 32 || s[k] == 0))
		k--;
	if (!(str = ft_strnew(k - i + 1)))
		return (NULL);
	while (i < k + 1)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
