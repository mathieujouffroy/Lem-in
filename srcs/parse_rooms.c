#include "lem_in.h"

int		is_room(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[0] == ' ' || line[0] == 'L' || line[0] == '#')
			return (FAILURE);
		while ((line[i] >= 33) && (line[i] <= 126))
			i++;
		if (line[i] != ' ')
			return (FAILURE);
		else
			i++;
		while (*line && ft_isdigit(line[i]))
			i++;
		if (line[i] != ' ')
			return (FAILURE);
		else
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

	i = 0;
	while (line[i] != ' ')
		i++;
	line[i] = '\0';
	return (ft_strdup(line));
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
	name = get_name(linetmp);
	hash = hashing((unsigned char*)name);
	if (is_hash_existing(*tmp, hash))
	{
		ft_printf("has does not exist\n");
		return (FAILURE);
	}
	links = memalloc_links();
	links->room = memalloc_graph();
	links->room->name = name;
	links->room->hash = hash;
	links->room->visited = false;
	links->room->index = lemin->cnt++;
	room_start_or_end(lemin, links);
/*	if (is_start(lemin))
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
*/
	addlinks(tmp, links);
	add_line_to_str(lemin, line);
	free(linetmp);
	!(lemin->state & S_ROOMS) ? (lemin->state |= S_ROOMS) : 0;
	return (SUCCESS);
}
