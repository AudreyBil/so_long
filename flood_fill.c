/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:25:28 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 14:45:16 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	**visited_allocate_memory(t_game *game)
{
	int	**visited;
	int	i;

	i = 0;
	visited = ft_calloc(sizeof (int *), game->nb_lines);
	if (!visited)
		return (NULL);
	while (i < game->nb_lines)
	{
		visited[i] = ft_calloc(sizeof (int), game->nb_col);
		if (!visited[i])
		{
			ft_printf("Error of memory allocation");
			free_visited(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

int	is_wall(int x, int y, t_game *game)
{
	if (game->map[x][y] == '1')
		return (1);
	return (0);
}

void	check_tiles(int x, int y, t_game *game, int **visited)
{
	if (is_wall(x, y, game) == 1 || visited[x][y] == 1)
		return ;
	visited[x][y] = 1;
	if (game->map[x][y] == 'C')
		game->check_nb_keb++;
	if (game->map[x][y] == 'E')
		game->check_nb_exit++;
	check_tiles(x - 1, y, game, visited);
	check_tiles(x + 1, y, game, visited);
	check_tiles(x, y - 1, game, visited);
	check_tiles(x, y + 1, game, visited);
}

void	player_position(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->nb_lines)
	{
		j = 0;
		while (j < game->nb_col)
		{
			if (game->map[i][j] == 'P')
			{
				game->player_x = i;
				game->player_y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}

int	flood_fill(t_game *game)
{
	int	x;
	int	y;
	int	**visited;
	int	i;

	i = 0;
	player_position(game);
	x = game->player_x;
	y = game->player_y;
	visited = visited_allocate_memory(game);
	if (!visited)
		return (1);
	game->check_nb_keb = 0;
	game->check_nb_exit = 0;
	check_tiles(x, y, game, visited);
	free_visited(visited, game->nb_lines);
	if (game->check_nb_keb != game->nb_kebab || game->check_nb_exit != 1)
		return (1);
	return (0);
}
