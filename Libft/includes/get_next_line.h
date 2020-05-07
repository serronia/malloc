/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.h                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aweiler <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2017/12/07 16:33:27 by aweiler      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 01:12:34 by jdarko      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 9999
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

typedef struct		s_stock
{
	char			*str;
	int				fd;
	struct s_stock	*next;
}					t_stock;

int					get_next_line(const int fd, char **line);

#endif
