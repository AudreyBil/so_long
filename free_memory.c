/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_memory.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:34:30 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 14:57:25 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	free_map(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_lines)
	{
		free(game->map[i]);
		i++;
	}
	free(game->map);
}

void	free_visited(int **visited, int nb_lines)
{
	int	i;

	i = 0;
	while (i < nb_lines)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}
