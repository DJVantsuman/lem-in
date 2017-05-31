/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_my_small_ants.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:17:31 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 17:34:50 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	get_useful_way(int count)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	g_u_way = (t_room_go***)malloc(sizeof(t_room_go **) * count + 1);
	while (g_good_ways[i])
	{
		l = length_way(g_good_ways[i]->way);
		g_u_way[i] = (t_room_go **)malloc(sizeof(t_room_go*) * l + 1);
		j = 0;
		while (g_good_ways[i]->way[j] && j < l)
		{
			g_u_way[i][j] = (t_room_go *)malloc(sizeof(t_room_go));
			g_u_way[i][j]->name = (char *)malloc(sizeof(char));
			g_u_way[i][j]->name = g_good_ways[i]->way[j];
			j++;
		}
		g_u_way[i][j] = NULL;
		i++;
	}
	g_u_way[i] = NULL;
}

void	fill_end_ants(int i)
{
	g_end_ant++;
	g_good_ways[i]->end_ant++;
}

void	print_running_ants(int count, int i, int j)
{
	while (g_end_ant < g_ant_h)
	{
		i = -1;
		while (g_u_way[++i])
		{
			j = g_good_ways[i]->index;
			while (j >= 0 && g_u_way[i][j]->num_ant &&
					g_good_ways[i]->end_ant <= g_good_ways[i]->count_ants &&
					g_u_way[i][j]->num_ant <= g_ant_h)
			{
				if (g_good_ways[i]->index < g_good_ways[i]->lenght - 1 &&
						g_u_way[i][j + 1]->num_ant != g_u_way[i][j]->num_ant)
					g_good_ways[i]->index++;
				print_ants(g_u_way[i][j]->num_ant, g_u_way[i][j]->name);
				if (ft_strcmp(g_u_way[i][j]->name, g_end) != 0)
					g_u_way[i][j + 1]->num_ant = g_u_way[i][j]->num_ant;
				else
					fill_end_ants(i);
				if ((g_u_way[i][j]->num_ant += count) > g_ant_h)
					g_u_way[i][j]->num_ant = 0;
				j--;
			}
		}
		write(1, "\n", 1);
	}
}

void	fill_ways_ant(void)
{
	int	i;
	int	ant;

	i = 0;
	ant = 1;
	while (g_u_way[i])
	{
		g_u_way[i][0]->num_ant = ant;
		i++;
		ant++;
	}
}

void	go_my_small_ants(char **farm, int count, int ant)
{
	int	i;

	ant = g_ant_h;
	while (ant > 0)
	{
		i = 0;
		while (g_good_ways[i] && ant >= g_good_ways[i]->lenght)
		{
			g_good_ways[i]->count_ants++;
			ant--;
			i++;
		}
		i = 0;
		if (ant < g_good_ways[i]->lenght)
			while (g_good_ways[i] && ant > 0)
			{
				g_good_ways[i]->count_ants++;
				ant--;
				i++;
			}
	}
	fill_ways_ant();
	print_farm(farm);
	write(1, "\n", 1);
	print_running_ants(count, 0, 0);
}
