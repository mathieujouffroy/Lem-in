/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybecret <ybecret@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/17 16:54:15 by ybecret           #+#    #+#             */
/*   Updated: 2019/06/06 12:24:35 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "libft.h"

# define GNL_BUFF_SIZE 6

typedef struct			s_fd
{
	char				*buff;
	int					fd;
	struct s_fd			*next;
}						t_fd;

int						get_next_line(const int fd, char **line);

#endif
