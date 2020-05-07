/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memmove.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:52:55 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:52:55 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if (src >= dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			len--;
			*((unsigned char *)dst + len) = *((unsigned char *)src + len);
		}
	}
	return (dst);
}
