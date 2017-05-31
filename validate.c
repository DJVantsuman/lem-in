/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/10 13:25:24 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 17:47:46 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

char	**write_way(char **way, char *name)
{
	int		i;
	char	**var_way;

	i = 0;
	while (way[i])
		i++;
	var_way = (char **)malloc(sizeof(char *) * ++i + 1);
	i = 0;
	while (way[i])
	{
		var_way[i] = ft_strsub(way[i], 0, ft_strlen(way[i]));
		i++;
	}
	var_way[i] = ft_strsub(name, 0, ft_strlen(name));
	var_way[++i] = NULL;
	return (var_way);
}

void	error_end(void)
{
	ft_putstr("ERROR\n");
	exit(1);
}

int		count_comand(char **farm, char *s)
{
	int count;
	int	i;

	count = 0;
	i = -1;
	while (farm[++i])
		if (ft_strcmp(farm[i], s) == 0)
			count++;
	return (count);
}

int		check_start_end(char **farm)
{
	int	i;

	i = 0;
	while (farm[i])
	{
		if (ft_strcmp(farm[i], "##start") == 0)
		{
			if (check_room(farm[i + 1]) == 0)
				return (0);
		}
		else if (ft_strcmp(farm[i], "##end") == 0)
		{
			if (check_room(farm[i + 1]) == 0)
				return (0);
		}
		i++;
	}
	return (1);
}
