/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:29:45 by abillote          #+#    #+#             */
/*   Updated: 2024/01/23 15:24:42 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	count_element(char c, int *nb_ex, int *nb_pl, int *nb_kebab)
{
	if (c == 'E')
		(*nb_ex)++;
	if (c == 'P')
		(*nb_pl)++;
	if (c == 'C')
		(*nb_kebab)++;
}

int	is_one_exit_one_player_one_collectible(t_game *game)
{
	int		nb_ex;
	int		nb_pl;
	int		i;
	int		j;

	nb_ex = 0;
	nb_pl = 0;
	game->nb_kebab = 0;
	i = 0;
	while (i < game->nb_lines)
	{
		j = 0;
		while (j < game->nb_col)
		{
			count_element(game->map[i][j], &nb_ex, &nb_pl, &(game->nb_kebab));
			j++;
		}
		i++;
	}
	if (nb_ex != 1 || nb_pl != 1 || game->nb_kebab < 1)
		return (1);
	return (0);
}

int	is_valid_map(t_game *game)
{
	if (is_rectangle_walls_characters(game) == 1)
		return (1);
	if (is_one_exit_one_player_one_collectible(game) == 1)
	{
		ft_printf("Error: Number of E, P or C is incorrect\n");
		return (1);
	}
	if (flood_fill(game) == 1)
	{
		ft_printf("Error: Exit or collectibles are not accessibles\n");
		return (1);
	}
	return (0);
}
