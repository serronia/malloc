/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbmot.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:52:56 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:52:56 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_nbmot(char const *str, char c)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == c && str[i - 1] != c)
			k++;
		i++;
	}
	if (str[i - 1] != c)
		k++;
	return (k);
}