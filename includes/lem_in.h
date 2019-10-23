/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yabecret <yabecret@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 10:53:32 by yabecret          #+#    #+#             */
/*   Updated: 2019/10/23 10:56:17 by yabecret         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define S_COLOR (1 << 4)
# define S_STEPS (1 << 5)

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
	bool				visited;
	bool				back;
	char				*name;
	char				*parent;
	unsigned long		pred;
	unsigned long		hash;
	int					index;
	unsigned int		antid;
	t_links				*links;
}						t_graph;

typedef	struct			s_allpaths
{
	t_links				*path;
	struct s_allpaths	*next;
	unsigned int		backward;
	unsigned int		len;
	unsigned int		nb_ants;
	unsigned int		max_steps;
	int					color_id;

}						t_allpaths;

typedef	struct			s_lemin
{
	unsigned int		nb_ants;
	unsigned int		ant_state;
	unsigned int		max_steps;
	unsigned int		max_steps1;
	unsigned int		total;
	unsigned int		reste;
	unsigned int		reste_ek;
	unsigned int		remainder;
	unsigned int		remainder_ek;
	unsigned int		path_max_len;
	unsigned int		path_max_lenbfs;
	unsigned int		path_max_lenek;
	int					state;
	int					color;
	char				*start;
	char				*end;
	char				*map;
	int					cnt;
	int					c_id;
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

void					add_line_and_delete(t_lemin *lemin, char *line);
void					add_line_and_delete(t_lemin *lemin, char *line);
int						gnl_exit(char *line);
int						success_exit(char *line);
int						parsing(t_lemin *lemin);

/*
**                 PARSE ANTS / COMMANDS
*/

int						ft_str_is_digit(char *str);
int						start_end(char *line);
int						get_ants(t_lemin *lemin, char *line);
void					add_command_to_state(t_lemin *lemin, char *line);

/*
**                     PARSE ROOMS
*/

char					*get_name(char *line);
void					room_start_or_end(t_lemin *lemin, t_links *links);
t_links					*init_links(t_lemin *lemin, char *name,
						unsigned long hash);
int						get_room(t_lemin *lemin, t_links **tmp, char *line);

/*
**                     CHECK DATA
*/

int						is_comment(char *line);
int						is_command(char *line);
int						is_start(t_lemin *lemin);
int						is_end(t_lemin *lemin);
int						is_room(char *line);

/*
**                     HASH
*/

unsigned long			hashing(unsigned char *str);
int						is_hash_existing(t_links *tmp, unsigned long hash);
int						are_hash_valid(t_links *tmp, unsigned long *h);
t_links					*find_hash_node(t_links *list, unsigned long hash);

/*
**                     PARSE LINKS
*/

int						get_link(t_lemin *lemin, t_links **tmp, char *line);
int						links_formatting(t_lemin *lemin, char *line);
void					addroom_links(t_links **list, t_links *l1,
						t_links *l2, char **rooms);
int						src_len(char *line, char c);

/*
**                     BACKWARD
*/

int						check_back_path(t_lemin *lemin, t_graph *room);
void					go_backwards(t_links **queue, t_links *list,
						t_graph *room, int back);

/*
**                     MEMORY ALLOCATION
*/

t_graph					*memalloc_graph(void);
t_links					*memalloc_links(void);
t_allpaths				*memalloc_allpaths(void);
int						**memalloc_matrix(int size);

/*
**                     DELETE
*/

void					delete_extra_node(t_lemin *lemin, t_allpaths *head);
void					delete_path_too_big(t_lemin *lemin, t_allpaths *head);

/*
**                     FREE
*/

int						freegraph(t_graph **graph);
int						freeroomlinks(t_links *list, int i);
int						freelist(t_links *links, int i);
int						freeallpaths(t_allpaths *allpaths);
int						freedata(t_lemin *lemin);
void					freelemin(t_lemin *lemin);

/*
**                     UTILS
*/

void					add_line_to_str(t_lemin *lemin, char *str);
void					addlinks(t_links **links, t_links *new);
void					printall(t_links *tmp);
void					print(t_links *head);
void					printmatrix(int **matrix, int size);

/*
**                     OPTIONS
*/

void					free_tab(char **tab);
int						check_coord(char **rooms);
int						ft_cntchr(char *str, char c);
int						display_color_ants(t_links *tmp, int id, int left);

/*
**                     ERRORS
*/

int						rooms_errors(t_lemin *lemin);
int						exit_with_message_room_duplicate(char *line);

/*
**                     BFS
*/

void					resetvisited(t_lemin *lemin);
int						backtrack(t_lemin *lemin);
int						bfs(t_lemin *lemin);
int						len_max(t_lemin *lemin, t_allpaths *head);
unsigned int			nbr_steps(t_lemin *lemin, t_allpaths *head,
						unsigned int max);
unsigned int			get_total(t_lemin *lemin, t_allpaths *head);
int						bfs_exit_or_malloc_path(t_lemin *lemin, int sink);
t_links					*init_queue_bfs(t_lemin *lemin);
int						sink_in_queue(t_lemin *lemin, t_links *queue);

/*
**                     queue
*/

void					enqueue_adjacent(t_lemin *lemin, t_links **queue,
						t_graph *room);
void					enqueue(t_links **links, t_links *new);
void					dequeue(t_links **links);
void					update_info_enqueue(t_links **queue, t_links *list,
						t_graph *room);

/*
**                     matrix
*/

int						updatefinalmatrices(t_lemin *lemin);
int						updatematrix(t_lemin *lemin);
int						updateweightmatrix(t_lemin *lemin);
void					addflow(int **matrix, int x, int y);
void					rmflow(int **matrix, int x, int y);
int						find_no_end_list(t_lemin *lemin);

int						ek(t_lemin *lemin);

/*
**                     CALCULUS
*/

unsigned int			max_steps_calculus(t_lemin *lemin, unsigned int len);
void					remainder_and_reste_calculus(t_lemin *lemin);
unsigned int			max_steps_calculus_ek(t_lemin *lemin, unsigned int len);
void					remainder_and_reste_calculus_ek(t_lemin *lemin,
						unsigned int total);

/*
**                     PATHS
*/

t_links					*find_index_node(t_links *list, int index);
int						find_nb_paths(t_lemin *lemin);
int						get_matrix_path(t_lemin *lemin);
void					sort_and_maxstepsek(t_lemin *lemin);
void					get_final_paths(t_lemin *lemin, unsigned int i);

/*
**                     sharing_ants
*/

int						sharing_ants(t_lemin *lemin);

/*
**                     display
*/

int						display_ants(t_lemin *lemin, t_allpaths	*paths,
						int left);

/*
**                     solve
*/

int						solve_lemin(t_lemin *lemin, unsigned int move);
int						move_and_display(t_lemin *lemin, t_allpaths *path);
void					move_ants(t_lemin *lemin, t_allpaths *paths);
void					fill_ants(t_lemin *lemin, t_allpaths *paths);

unsigned int			get_total2(t_lemin *lemin, t_allpaths *head, int index);
int						max_stepsek(t_lemin *lemin, t_allpaths *head);

t_allpaths				*sort_paths(t_allpaths *container);

int						exit_with_message_room(char *line);
int						exit_with_message_links(char *line);
int						exit_with_message_coord_overflow(char *line);

int						parse_room(t_lemin *lemin, char *line);
int						parse_links(t_lemin *lemin, char *line);

#endif
