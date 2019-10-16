#include "lem_in.h"

int		is_room(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[0] == ' ' || line[0] == 'L' || line[0] == '#')
			return (FAILURE);
		while ((line[i] >= 33) && (line[i] <= 126) && (line[i] != 45))
			i++;
		if (line[i] != ' ')
			return (FAILURE);
		else
			i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		while (*line && ft_isdigit(line[i]))
			i++;
		if (line[i] != ' ')
			return (FAILURE);
		else
			i++;
		if (line[i] == '-' || line[i] == '+')
			i++;
		while (*line && ft_isdigit(line[i]))
			i++;
		if (line[i] != '\0')
			return (FAILURE);
	}
	return (SUCCESS);
}

char	*get_name(char *line)
{
	int i;
	char **rooms;

	i = 0;
	rooms = ft_strsplit(line, ' ');
//	while (line[i] != ' ')
//		i++;
//	line[i] = '\0';
//	return (ft_strdup(line));
	ft_printf("{green}room 0 : %s\n{reset}", rooms[0]);
	ft_printf("room 1 : %s\n", rooms[1]);
	ft_printf("room 2 : %s\n", rooms[2]);
	if ((!ft_atoi(rooms[1]) && ft_strcmp(rooms[1], "0")) 
		|| (!ft_atoi(rooms[2]) && ft_strcmp(rooms[2], "0")))
	{
		free(rooms[1]);
		free(rooms[2]);
		return (NULL);
	}
	free(rooms[1]);
	free(rooms[2]);
	return (rooms[0]);
}

void	room_start_or_end(t_lemin *lemin, t_links *links)
{
	if (is_start(lemin))
	{
		lemin->start = links->room->name;
		lemin->hashstart = links->room->hash;
		lemin->head = links->room;
	}
	else if (is_end(lemin))
	{
		lemin->end = links->room->name;
		lemin->hashend = links->room->hash;
		lemin->sink = links->room;
	}
}

int		get_room(t_lemin *lemin, t_links **tmp, char *line)
{
	t_links			*links;
	char			*name;
	char			*linetmp;
	unsigned long	hash;

	linetmp = ft_strdup(line);
	if ((name = get_name(linetmp)) == NULL)
		return (-1);
	hash = hashing((unsigned char*)name);
	if (is_hash_existing(*tmp, hash))
		return (FAILURE);
	links = memalloc_links();
	links->room = memalloc_graph();
	links->room->name = name;
	links->room->hash = hash;
	links->room->visited = false;
	links->room->index = lemin->cnt++;
	room_start_or_end(lemin, links);
	addlinks(tmp, links);
	add_line_to_str(lemin, line);
	free(linetmp);
	!(lemin->state & S_ROOMS) ? (lemin->state |= S_ROOMS) : 0;
	return (SUCCESS);
}
