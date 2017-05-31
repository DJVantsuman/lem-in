/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:27:33 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 18:01:44 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft/libft.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct		s_room
{
	char			*name;
	int				x;
	int				y;
	int				flag;
	struct s_room	*next;
	char			**links;
}					t_room;

typedef struct		s_link
{
	char			*name1;
	char			*name2;
	struct s_link	*next;
}					t_link;

typedef struct		s_way
{
	char			**way;
	int				lenght;
	int				count_ants;
	int				end_ant;
	int				index;
	struct s_way	*next;
}					t_way;

typedef struct		s_go_room
{
	char			*name;
	int				num_ant;
}					t_room_go;

int					g_ant_h;
int					g_end_ant;
char				*g_start;
char				*g_end;
t_way				**g_ways;
t_way				**g_sort_way;
t_way				**g_good_ways;
t_room_go			***g_u_way;

int					check_start_end(char **farm);
int					count_comand(char **farm, char *s);
int					check_room(char *s);
int					check_one_room(t_room *start, char *name);
int					check_link(char *link, t_room **begin_room);
int					write_room(char **farm, t_room **begin_room);
int					length_way(char **way);

void				write_link(char **farm, t_link **start_link, t_room **b);
void				find_way(t_room *room, t_link *link, char **farm);
void				ant_is_runing(char **farm);
void				get_useful_way(int count);
void				go_my_small_ants(char **farm, int count, int ant);
void				print_farm(char **farm);
void				print_ants(int ant, char *room);
void				print_useful_ways();
void				error_end();
void				arrey_del(char **as);
void				free_oll_memory(t_room	*begin_room, t_link	*start_link);

char				**write_way(char **way, char *name);
#endif
