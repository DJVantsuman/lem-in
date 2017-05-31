/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_room.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 17:15:28 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 21:17:29 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	write_valid_room(char *room, t_room **begin_room)
{
	int		i;
	int		j;
	t_room	*var_room;

	i = 0;
	j = 0;
	var_room = (t_room*)malloc(sizeof(t_room));
	while (room[i] == ' ' || room[i] == '\t')
		i++;
	while (room[i] != ' ' && room[i] != '\0' && ++j)
		i++;
	var_room->name = (char *)malloc(sizeof(char) * j + 1);
	i -= j + 1;
	j = 0;
	while (room[++i] != ' ')
		var_room->name[j++] = room[i];
	var_room->x = ft_atoi(room + i);
	i++;
	while (room[i] != ' ')
		i++;
	var_room->y = ft_atoi(room + i);
	var_room->next = *begin_room;
	*begin_room = var_room;
}

int		check_room(char *s)
{
	int	i;
	int	count;
	int n;

	i = -1;
	count = 0;
	n = 0;
	while (s && s[++i])
		if (s[i] == ' ')
			count++;
	i = 0;
	while (s && s[i] && s[i] != ' ')
		i++;
	while (s && s[++i])
	{
		while (s[i] >= 48 && s[i] <= 57)
			i++;
		if ((s[i] == ' ' || s[i] == '\0') && (s[i - 1] >= 48 && s[i - 1] <= 57))
			n++;
	}
	if (count != 2 || ft_strstr(s, "-") != 0 || s[0] == 'L' || n != 2)
		return (0);
	return (1);
}

int		write_room(char **farm, t_room **begin_room)
{
	int	i;

	i = 1;
	(*begin_room)->next = NULL;
	(*begin_room)->name = NULL;
	(*begin_room)->links = NULL;
	while (farm[i])
	{
		while (farm[i] && farm[i][0] == '#')
			i++;
		if (check_room(farm[i]))
			write_valid_room(farm[i], begin_room);
		else if (check_link(farm[i], begin_room) == 1)
			return (1);
		else
			return (0);
		i++;
	}
	return (0);
}
