/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 15:24:20 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 14:52:23 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

char	**store_map(char *file, int nb_lines)
{
	char	**map;
	int		i;
	int		fd;
	int		j;

	i = 0;
	j = 0;
	fd = open(file, O_RDONLY);
	map = malloc(sizeof(char *) * (nb_lines + 1));
	if (!map)
	{
		ft_printf("\n--Error--\n Memory allocation");
		exit (EXIT_FAILURE);
	}
	while (i < nb_lines)
	{
		map[i] = get_next_line(fd);
		i++;
	}
	close(fd);
	return (map);
}

int	map_count_lines(int fd)
{
	int		nb_lines;
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("\n--Error--\nMap is empty\n\n");
		exit (EXIT_FAILURE);
	}
	free(line);
	nb_lines = 0;
	while (line != NULL)
	{
		line = get_next_line(fd);
		free(line);
		nb_lines++;
	}
	return (nb_lines);
}

void	read_map(char *file, t_game *game)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("\n--Error--\nMap does not open\n\n");
		exit (EXIT_FAILURE);
	}
	game->nb_lines = map_count_lines(fd);
	close(fd);
	game->map = NULL;
	game->map = store_map(file, game->nb_lines);
	if (is_valid_map(game) == 1)
	{
		free_map(game);
		exit (1);
	}
}
