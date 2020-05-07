/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_atoi.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jdarko <marvin@le-101.fr>                  +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/15 15:51:10 by jdarko       #+#   ##    ##    #+#       */
/*   Updated: 2017/12/15 15:51:38 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "includes/libft.h"

int		ft_atoi(const char *str)
{
	int		i;
	long	nb;
	int		neg;

	i = 0;
	nb = 0;
	neg = 1;
	while (str[i] == '\t' || str[i] == '\f' || str[i] == '\v' || str[i] == '\n'
			|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nb = nb * 10 + (str[i] - 48);
		if (i > 20)
			return (neg == -1 ? 0 : -1);
		i++;
	}
	return (nb * neg);
}
