/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/28 20:17:31 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 17:45:55 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	arrey_del(char **as)
{
	int i;

	i = 0;
	while (as[i])
	{
		free(as[i]);
		as[i] = NULL;
		i++;
	}
	free(as);
}

void	print_farm(char **farm)
{
	int i;

	i = 0;
	while (farm[i])
	{
		ft_putstr(farm[i]);
		write(1, "\n", 1);
		i++;
	}
	arrey_del(farm);
}

void	print_ants(int ant, char *room)
{
	ft_putchar('L');
	ft_putnbr(ant);
	ft_putchar('-');
	ft_putstr(room);
	write(1, " ", 1);
}

int		length_way(char **way)
{
	int i;

	i = 0;
	while (way[i])
		i++;
	return (i - 1);
}

void	print_useful_ways(void)
{
	int i;
	int j;

	i = 0;
	ft_putstr("\n\nUsed paths:\n");
	while (g_good_ways[i])
	{
		j = 0;
		ft_putstr("way №");
		ft_putnbr(i + 1);
		ft_putstr(": ");
		ft_putstr(g_start);
		ft_putstr(", ");
		while (g_good_ways[i]->way[j + 1][0] != '\0')
		{
			ft_putstr(g_good_ways[i]->way[j]);
			ft_putstr(", ");
			j++;
		}
		ft_putstr(g_good_ways[i]->way[j]);
		ft_putstr("\n");
		i++;
	}
}
