/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_link.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: itsuman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/12 19:33:13 by itsuman           #+#    #+#             */
/*   Updated: 2017/05/14 21:28:10 by itsuman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		check_full_link(char *name1, char *name2, char *link)
{
	char	*str;
	char	*str_free;
	int		n;

	n = 0;
	str = ft_strjoin(name1, "-");
	str_free = str;
	str = ft_strjoin(str, name2);
	if (ft_strcmp(str, link) == 0)
		n++;
	else
	{
		free(str);
		free(str_free);
		str = ft_strjoin(name2, "-");
		str_free = str;
		str = ft_strjoin(str, name1);
		if (ft_strcmp(str, link) == 0)
			n++;
	}
	free(str_free);
	free(str);
	if (n == 1)
		return (1);
	return (0);
}

int		check_link(char *link, t_room **begin_room)
{
	int		count;
	char	*name1;
	char	*name2;
	t_room	*var;

	count = 0;
	var = *begin_room;
	while (var->next != NULL)
	{
		if (ft_strstr(link, var->name))
		{
			if (count == 0)
				name1 = var->name;
			else if (count == 1)
				name2 = var->name;
			count++;
		}
		var = var->next;
	}
	if (link && (link[0] == ' ' || check_full_link(name1, name2, link) == 0))
		return (0);
	return (1);
}

void	write_link_name(char *link, t_room **begin_room, t_link **start_link)
{
	t_link	*var_link;
	t_room	*var_begin_room;

	var_link = (t_link *)malloc(sizeof(t_link));
	var_begin_room = *begin_room;
	while (var_begin_room->next)
	{
		if (ft_strstr(link, var_begin_room->name) != 0 &&
				var_link->name1 == NULL)
		{
			var_link->name1 = var_begin_room->name;
		}
		else if (ft_strstr(link, var_begin_room->name) != 0 &&
				var_link->name2 == NULL)
			var_link->name2 = var_begin_room->name;
		var_begin_room = var_begin_room->next;
	}
	var_link->next = *start_link;
	*start_link = var_link;
}

void	write_link(char **farm, t_link **start_link, t_room **begin_room)
{
	int	i;
	int l;

	i = 0;
	l = length_way(farm);
	while (farm[i] && check_link(farm[i], begin_room) == 0)
		i++;
	while (farm[i] && i <= l)
	{
		while (i <= l && farm[i][0] == '#')
			i++;
		if (farm[i] && check_link(farm[i], begin_room))
			write_link_name(farm[i], begin_room, start_link);
		else if (farm[i])
			error_end();
		i++;
	}
}
