/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:53:02 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:53:02 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**ret;
	int		i;
	int		j;
	int		k;

	if (!(s) || !(ret = (char**)malloc(sizeof(*ret) * (ft_nbmot(s, c)) + 1)))
		return (NULL);
	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i] != '\0')
		{
			j = 0;
			if (!(ret[k] = (char*)malloc(sizeof(**ret) * (ft_lm(s, i, c)) + 1)))
				return (NULL);
			while (s[i] != c && s[i])
				ret[k][j++] = s[i++];
			ret[k++][j] = '\0';
		}
	}
	ret[k] = NULL;
	return (ret);
}
