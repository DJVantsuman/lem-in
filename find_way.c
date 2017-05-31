/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_way.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:17:31 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 21:18:00 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_valid_way(t_way *way, int flag, t_room *room)
{
	t_way	*var_way;
	char	**del;
	int		i;

	if (flag == 1)
	{
		var_way = (t_way *)malloc(sizeof(t_way));
		del = var_way->way;
		var_way->lenght = way->lenght;
		var_way->way = write_way(way->way, "");
		free(del);
		var_way->next = *g_ways;
		*g_ways = var_way;
	}
	else
	{
		i = 0;
		while (way->way[i])
			i++;
		way->way[i - 1] = 0;
		way->lenght--;
		room->flag = 0;
	}
}

void	find_valid_ways(t_room *startr, t_way *way, char *name, char *room_befo)
{
	t_room	*room;
	int		i;

	i = 0;
	room = startr;
	way->way = write_way(way->way, name);
	way->lenght++;
	while (ft_strcmp(room->name, name) != 0)
		room = room->next;
	if (ft_strcmp(name, g_end) == 0)
		write_valid_way(way, 1, room);
	room->flag = 1;
	while (room->links[i] && ft_strcmp(name, g_end) != 0)
	{
		if (ft_strcmp(room->links[i], room_befo) != 0 &&
				ft_strcmp(room->links[i], g_start) != 0 &&
				check_one_room(startr, room->links[i]))
			find_valid_ways(startr, way, room->links[i], room->name);
		i++;
	}
	write_valid_way(way, 2, room);
}

char	**write_room_link(char **links, char *name_room)
{
	int		i;
	char	**var_links;

	i = 0;
	while (links[i])
		i++;
	var_links = (char **)malloc(sizeof(char *) * ++i + 1);
	i = 0;
	while (links[i])
	{
		var_links[i] = ft_strsub(links[i], 0, ft_strlen(links[i]));
		i++;
	}
	var_links[i] = ft_strsub(name_room, 0, ft_strlen(name_room));
	var_links[++i] = NULL;
	arrey_del(links);
	return (var_links);
}

void	find_link(t_room *vroom, t_link *vlink)
{
	t_link	*link;

	link = vlink;
	while (vroom->next)
	{
		vlink = link;
		vroom->links = (char **)malloc(sizeof(char *));
		vroom->links[0] = NULL;
		while (vlink->next)
		{
			if (ft_strcmp(vroom->name, vlink->name1) == 0)
				vroom->links = write_room_link(vroom->links, vlink->name2);
			else if (ft_strcmp(vroom->name, vlink->name2) == 0)
				vroom->links = write_room_link(vroom->links, vlink->name1);
			vlink = vlink->next;
		}
		vroom = vroom->next;
	}
}

void	find_way(t_room *start_room, t_link *link, char **farm)
{
	t_room	*vroom;
	t_link	*vlink;
	t_way	*way;
	int		i;

	vroom = start_room;
	vlink = link;
	g_ways = (t_way **)malloc(sizeof(t_way *));
	(*g_ways) = (t_way *)malloc(sizeof(t_way));
	(*g_ways)->way = (char **)malloc(sizeof(char *));
	(*g_ways)->way[0] = NULL;
	i = -1;
	find_link(vroom, vlink);
	vroom = start_room;
	while (ft_strcmp(vroom->name, g_start) != 0)
		vroom = vroom->next;
	while (vroom->links[++i])
	{
		way = (t_way *)malloc(sizeof(t_way));
		way->way = (char **)malloc(sizeof(char *));
		way->way[0] = NULL;
		way->lenght = 0;
		find_valid_ways(start_room, way, vroom->links[i], vroom->name);
	}
	ant_is_runing(farm);
}
