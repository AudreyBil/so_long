/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 17:25:04 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 15:17:29 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

int	is_enclosed_by_walls(t_game *game)
{
	int	j;
	int	i;

	i = 0;
	while (i < game->nb_lines)
	{
		j = 0;
		while (j < game->nb_col)
		{
			if ((i == 0 || i == game->nb_lines - 1) && game->map[i][j] != '1')
				return (1);
			if ((j == 0 || j == game->nb_col - 1) && game->map[i][j] != '1')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	characters_not_correct(t_game *game)
{
	int		j;
	int		i;
	char	*characters;

	i = 0;
	characters = "EP01C";
	while (i < game->nb_lines)
	{
		j = 0;
		while (j < game->nb_col)
		{
			if (ft_strchr(characters, game->map[i][j]) == NULL)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	is_rectangle(t_game *game)
{
	int	i;

	i = 0;
	game->nb_col = ft_strlen(game->map[i]) - 1;
	while (i < game->nb_lines)
	{
		if (ft_strlen(game->map[i]) != ft_strlen(game->map[0]))
			return (1);
		i++;
	}
	return (0);
}

int	is_rectangle_walls_characters(t_game *game)
{
	if (is_rectangle(game) == 1)
	{
		ft_printf("\n--Error--\nMap is not a rectangle\n\n");
		return (1);
	}
	if (characters_not_correct(game) == 1)
	{
		ft_printf("\n--Error--\nThere are incorrect characters in the map\n\n");
		return (1);
	}
	if (is_enclosed_by_walls(game) == 1)
	{
		ft_printf("\n--Error--\nMap is not enclosed by walls\n");
		return (1);
	}
	return (0);
}
