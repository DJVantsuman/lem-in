/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:17:31 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 17:27:03 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_one_room(t_room *start, char *name)
{
	t_room	*room;

	room = start;
	while (ft_strcmp(room->name, name) != 0)
		room = room->next;
	if (room->flag == 1)
		return (0);
	return (1);
}

void	del_t_way(t_way **sum_way)
{
	t_way	*var_way;
	t_way	*del;

	if (sum_way)
	{
		var_way = *sum_way;
		if (var_way)
		{
			while (var_way->next)
			{
				del = var_way;
				if (var_way->way)
					arrey_del(var_way->way);
				var_way = var_way->next;
				free(del);
			}
		}
		free(sum_way);
	}
}

void	free_oll_memory(t_room *begin_room, t_link *start_link)
{
	del_t_way(g_sort_way);
	begin_room = 0;
	start_link = 0;
}
