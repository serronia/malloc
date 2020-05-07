/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memset.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:52:56 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:52:56 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*t;

	t = b;
	while (len > 0)
	{
		*t = (unsigned char)c;
		len--;
		t++;
	}
	return (b);
}
