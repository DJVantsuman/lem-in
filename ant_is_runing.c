/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_is_runing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:17:31 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 17:10:51 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_intersection(char **way)
{
	int i;
	int j;
	int t;

	i = 0;
	while (g_good_ways[i])
	{
		j = 0;
		while (ft_strcmp(g_good_ways[i]->way[j], "") != 0)
		{
			t = 0;
			while (way[t])
			{
				if (ft_strcmp(g_good_ways[i]->way[j], way[t]) == 0 &&
					ft_strcmp(way[t], g_end) != 0)
					return (0);
				t++;
			}
			j++;
		}
		i++;
	}
	return (1);
}

void	get_good_ways(int count)
{
	int	i;
	int	j;
	int	n;
	int	sum_length;

	i = 0;
	j = 0;
	n = g_ant_h;
	g_good_ways = (t_way **)malloc(sizeof(t_way *) * count + 1);
	sum_length = g_sort_way[i]->lenght;
	g_good_ways[j++] = g_sort_way[i++];
	n--;
	while (g_sort_way[i] && n >= sum_length)
	{
		if (check_intersection(g_sort_way[i]->way))
		{
			g_good_ways[j] = g_sort_way[i];
			sum_length += g_sort_way[i]->lenght;
			j++;
			n--;
		}
		i++;
	}
	g_good_ways[j] = NULL;
}

int		check_ways(void)
{
	t_way	*var_ways;
	int		i;

	var_ways = (*g_ways);
	i = 0;
	while (var_ways->next)
	{
		i++;
		var_ways = var_ways->next;
	}
	if (i == 0)
		error_end();
	return (i);
}

void	sort_ways(int count, int max_length)
{
	int		i;
	int		j;
	t_way	*start;

	i = 0;
	j = 0;
	g_sort_way = (t_way **)malloc(sizeof(t_way *) * count + 1);
	while (i <= max_length)
	{
		start = (*g_ways);
		while (start)
		{
			if (start->lenght == i && start->lenght > 0)
			{
				g_sort_way[j] = start;
				j++;
			}
			start = start->next;
		}
		i++;
	}
	g_sort_way[count] = NULL;
}

void	ant_is_runing(char **farm)
{
	int		count;
	int		max_length;
	t_way	*start;

	count = check_ways();
	max_length = 0;
	start = (*g_ways);
	while (start->next)
	{
		if (max_length < start->lenght)
			max_length = start->lenght;
		start = start->next;
	}
	sort_ways(count, max_length);
	get_good_ways(count);
	count = 0;
	while (g_good_ways[count])
		count++;
	get_useful_way(count);
	go_my_small_ants(farm, count, 0);
	print_useful_ways();
}
