/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sl_read_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharnvon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 11:34:56 by sharnvon          #+#    #+#             */
/*   Updated: 2022/06/28 11:45:59 by sharnvon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "./getnextline/get_next_line.h"
#include "./libft/libft.h"

char	**sl_join_map(char **rts, char *str)
{
	char	**result;
	int		index;
	int		xedni;

	index = 0;
	if (str == NULL)
		return (rts);
	if (rts == NULL)
		result = (char **)ft_calloc(sizeof(char *), 2);
	else
		result = (char **)ft_calloc(sizeof(char *), sl_checklen(rts, NULL, 1) + 2);
	if (result == NULL)
	{
		/* free another result that use to malloc ??*/
		exit(0);
	}
	while (rts != NULL && rts[index] != NULL)
	{
		xedni = 0;
		result[index] = (char *)ft_calloc(sizeof(char), sl_checklen(NULL, rts[index], 3) + 1);
		if (result == NULL)
		{
			/* free another result that use to malloc ??*/
			exit(0);
		}
		while (rts[index][xedni] != '\0' && rts[index][xedni] != '\n')
		{
			result[index][xedni] = rts[index][xedni];
			xedni++;
		}
		result[index][xedni] = '\0';
		index++;
	}
	result[index] = (char *)ft_calloc(sizeof(char *), sl_checklen(NULL, str, 3) + 1);
	if (result == NULL)
	{
		/* free another result that use to malloc ??*/
		exit(0);
	}
	xedni = 0;
	while (str[xedni] != '\0' && str[xedni] != '\n')
	{
		result[index][xedni] = str[xedni];
		xedni++;
	}
	result[++index] = NULL;
	if (rts != NULL)
	{
		index = 0;
		while (rts[index] != NULL)
			free(rts[index++]);
		free(rts);
	}
	free(str);
	return (result);
}

char	**sl_read_map(char **argv)
{
	char	**result;
	char	*line;
	int		index;
	int		fd;

	result = NULL;
	index = 0;
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (0);
	while (0 < 1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		result = sl_join_map(result, line);
		if (result == NULL)
			break ;
	}
	close(fd);
	return (result);
}

char **sl_make_mmap(char **map)
{
	char	**result;
	int		index;
	int		xedni;
	
	index = 0;
	result = (char **)ft_calloc(sizeof(char *), sl_checklen(map, NULL, 1) + 1);
	if (result == NULL)
	{
		/* free  another malloc */
		exit(0);
	}
	while (map[index] != NULL)
	{
		xedni = 0;
		result[index] = (char *)ft_calloc(sizeof(char), sl_checklen(NULL, map[index], 2) + 1);
		if (result[index] == NULL)
		{
			/* free another malloc */
			exit(0);
		}
		while (map[index][xedni] != '\0')
		{
			if (sl_checkcompair (NULL, "PC", map[index][xedni], 2) != 0)
				result[index][xedni] = '0';
			else
				result[index][xedni] = map[index][xedni];
			xedni++;
		}
		index++;
	}
	return (result);
}

char **sl_make_map(char **map)
{
	int		index;
	int		xedni;
	char	*extra;

	index = 0;
	while (map[index] != NULL)
	{
		xedni = 0;
		while (map[index][xedni] != '\0')
		{
			if (map[index][xedni] == 'M')
				map[index][xedni] = '0';
			xedni++;
		}
		index++;
	}
	extra = (char *)ft_calloc(sizeof(char), sl_checklen(NULL, map[0], 2) + 1);
	if (extra == NULL)
		//free//
		return (0);
	while (--index >= 0)
	{
		printf("index= %d\n", index);
		extra[index] = '1';
	}
	printf("extra= %s\n", extra);
	map = sl_join_map(map, extra);
	return (map);
}
