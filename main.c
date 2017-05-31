/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/06 13:25:24 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/17 14:00:08 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_position(char *room, int n)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((room[i] == ' ' || room[i] == '\t') && room[i] != '\0')
		i++;
	while (room[i] != ' ' && room[i] != '\0' && ++j)
		i++;
	if (n == 1)
		g_start = (char *)malloc(sizeof(char) * (i - j) + 1);
	else
		g_end = (char *)malloc(sizeof(char) * (i - j) + 1);
	i -= j;
	j = 0;
	while (room[i] != ' ' && room[i] != '\0')
	{
		if (n == 1)
			g_start[j] = room[i];
		else
			g_end[j] = room[i];
		i++;
		j++;
	}
}

void	write_start_end(char **farm)
{
	int	i;

	i = 0;
	while (farm[i])
	{
		if (ft_strcmp(farm[i], "##start") == 0)
			write_position(farm[i + 1], 1);
		else if (ft_strcmp(farm[i], "##end") == 0)
			write_position(farm[i + 1], 2);
		i++;
	}
}

int		check_ant(char **farm)
{
	int	i;

	i = 0;
	while (farm[0][i])
		if (farm[0][i] >= 48 && farm[0][i] <= 57)
			i++;
		else
			return (0);
	if (i == 1 && farm[0][0] == '0')
		return (0);
	return (1);
}

void	write_farm(char **farm)
{
	t_room	*begin_room;
	t_link	*start_link;

	begin_room = (t_room *)malloc(sizeof(t_room));
	start_link = (t_link *)malloc(sizeof(t_link));
	start_link->next = NULL;
	if (check_ant(farm))
		g_ant_h = ft_atoi(farm[0]);
	else
		error_end();
	if (count_comand(farm, "##start") == 1 && count_comand(farm, "##end") == 1
			&& check_start_end(farm) == 1)
		write_start_end(farm);
	else
		error_end();
	if (write_room(farm, &begin_room) == 1)
		write_link(farm, &start_link, &begin_room);
	else
		error_end();
	find_way(begin_room, start_link, farm);
	free_oll_memory(begin_room, start_link);
}

int		main(void)
{
	char	*line;
	char	*str;
	char	**farm;
	int		n;

	str = "";
	while (1)
		if ((n = get_next_line(0, &line)) == -1)
			error_end();
		else if (n == 0)
		{
			if (line)
				free(line);
			break ;
		}
		else
		{
			if (ft_strcmp(line, "") == 0)
				error_end();
			str = ft_strjoin(str, ft_strjoin(line, "\n"));
			free(line);
		}
	farm = ft_strsplit(str, '\n');
	write_farm(farm);
	return (0);
}
