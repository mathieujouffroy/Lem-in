#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include <stdbool.h>

# define FD		 0
# define SUCCESS 1
# define FAILURE 0
# define S_ROOMS (1 << 0)
# define S_LINKS (1 << 1)
# define S_START (1 << 2)
# define S_END   (1 << 3)
# define S_BACKWARD (1 << 4)

# define S_R1 (1 << 0)
# define S_R2 (1 << 1)

# define S_FREE (1 << 4)


typedef struct			s_links
{
	struct s_graph		*room;
	struct s_links		*next;
}						t_links;

typedef struct			s_graph
{
	long				x;
	long 				y;
	bool				visited;
	bool				back;
	char				*name;
	char				*parent;
	unsigned long		pred;
	unsigned long		hash;
	int					index;
	int					weight;
	int					used;
	unsigned int		antid;
	t_links				*links;
}						t_graph;

typedef	struct 			s_allpaths
{
	t_links				*path;
	struct s_allpaths	*next;
	unsigned int		backward;
	unsigned int		len;
	unsigned int		nb_ants;
	unsigned int		max_steps;

}						t_allpaths;

typedef	struct			s_lemin
{
	unsigned int		nb_ants;
	unsigned int		ant_state;
	unsigned int		max_steps;
	unsigned int		max_steps1;
	unsigned int		total;
	unsigned int		reste;
	unsigned int		remainder;
	unsigned int		path_max_len;
	unsigned int		path_max_lenbfs;
	unsigned int		path_max_lenek;
	int					state;
	char                *start;
	char				*end;
	char				*map;
	int					cnt;
	unsigned int		nb_pathsbfs;
	unsigned int		nb_pathsek;
	unsigned int		nb_paths;
	unsigned long		hashstart;
	unsigned long		hashend;
	int					**matrix;
	t_links				*list;
	t_graph				*head;
	t_graph				*sink;
	t_allpaths			*debut;
	t_allpaths			*container;
	t_allpaths			*container1;
}						t_lemin;


/*
**                     PARSING
*/

int			start_end(char *line);
int			parsing(t_lemin *lemin);
int			gnl_exit(char *line);

/*
**                     PARSE ANTS
*/

int			ft_str_is_digit(char *str);
int			get_ants(t_lemin *lemin);

/*
**                     PARSE ROOMS
*/

char		*get_name(char *line);
int			is_room(char *line);
int			is_start(t_lemin *lemin);
int			is_end(t_lemin *lemin);
int			get_room(t_lemin *lemin, t_links **tmp, char *line);

/*
**                     CHECK DATA
*/

int			is_comment(char *line);
int			is_command(char *line);
int			is_room_existing(t_links *tmp, char *name);
int			is_hash_existing(t_links *tmp, unsigned long hash);
int			are_hash_valid(t_links *tmp, unsigned long *h);
int			are_rooms_valid(t_links *tmp, char *r1, char *r2);


/*
**                     PARSE LINKS
*/

int		get_link(t_lemin *lemin, t_links **tmp, char *line);
void	addroom_links(t_links **list, t_links *l1, t_links *l2, char **rooms);
int		src_len(char *line, char c);


/*
**                     MEMORY ALLOCATION
*/

t_graph		*memalloc_graph(void);
t_links		*memalloc_links(void);
t_allpaths	*memalloc_allpaths(void);
int			**memalloc_matrix(int size);

/*
**                     FREE
*/

int freegraph(t_graph **graph);
int freelinks(t_links **links);
int freeallpaths(t_allpaths **allpaths);
void freelemin(t_lemin *lemin);

/*
**                     UTILS
*/

void	add_line_to_str(t_lemin *lemin, char *str);
void	addlinks(t_links **links, t_links *new);
void	printall(t_links *tmp);
void	print(t_links *head);
void 	printmatrix(int **matrix, int size);
unsigned long hashing(unsigned char *str);

/*
**                     ERRORS
*/

int			rooms_errors(t_lemin *lemin);
int		exit_with_message_room_duplicate(char *line);

/*
**                     BFS
*/

t_links			*find_hash_node(t_links *list, unsigned long hash);
void			resetvisited(t_lemin *lemin);
int				backtrack(t_lemin *lemin);
int				bfs(t_lemin *lemin);
int				len_max(t_lemin *lemin, t_allpaths *head);
unsigned int	nbr_steps(t_lemin *lemin, t_allpaths *head, unsigned int max);
unsigned int	get_total(t_lemin *lemin, t_allpaths *head);

/*
**                     queue
*/

void	enqueue_adjacent(t_lemin *lemin, t_links **queue, t_graph *room);
void	enqueue(t_links **links, t_links *new);
void	dequeue(t_links **links);
void	update_info_enqueue(t_links **queue, t_links *list, t_graph *room);
void	go_backwards(t_links **queue, t_links *list, t_graph *room, int back);

/*
**                     matrix
*/

void	get_final_paths(t_lemin *lemin);
int		updatefinalmatrices(t_lemin *lemin);
int		updatematrix(t_lemin *lemin);
int		updateweightmatrix(t_lemin *lemin);
void	addflow(int **matrix, int x, int y);
void	rmflow(int **matrix, int x, int y);
int		find_no_end_list(t_lemin *lemin);

int	ek(t_lemin *lemin);

/*
**                     backtrack
*/

int		get_matrix_path(t_lemin *lemin, t_links *tmp);

/*
**                     sharing_ants
*/

int		sharing_ants(t_lemin *lemin);

/*
**                     display
*/

int		display_ants(t_allpaths	*paths, int left);

/*
**                     solve
*/

int		solve_lemin(t_lemin *lemin, unsigned int move);
int		move_and_display(t_lemin *lemin, t_allpaths *path);
void	move_ants(t_lemin *lemin, t_allpaths *paths);
void	fill_ants(t_lemin *lemin, t_allpaths *paths);


unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index);
int						max_stepsek(t_lemin *lemin, t_allpaths *head);

t_allpaths *sort_paths(t_allpaths *container);


void		delete_extra_node(t_lemin *lemin, t_allpaths *head);

int			exit_with_message_room(char *line);
int			exit_with_message_links(char *line);
int			exit_with_message_coord_overflow(char *line);

#endif
