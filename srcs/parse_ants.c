#include "lem_in.h"

int		ft_str_is_digit(char *str)
{
	while (ft_isdigit(*str))
		str++;
	return (*str == '\0' ? SUCCESS : FAILURE);
}

int		get_ants(t_lemin *lemin)
{
	char *line;

	line = NULL;
	while (get_next_line(FD, &line) == 1)
	{
		if (is_comment(line) && !S_ROOMS)
			ft_strdel(&line);
		else if (ft_str_is_digit(line))
		{
			lemin->nb_ants = ft_atoi(line);
			add_line_to_str(lemin, line);
			return (SUCCESS);
		}
		else
		{
			ft_strdel(&line);
			return (FAILURE);
		}
		ft_strdel(&line);
	}
	return (FAILURE);
}
