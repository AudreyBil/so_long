/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:53:42 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 15:43:40 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	print_mvm_count(t_game *game)
{
	game->mvm_count++;
	ft_printf("Number of movements : %d\n", game->mvm_count);
}

void	print_collectibles_player_exit(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->nb_lines)
	{
		y = 0;
		while (y < game->nb_col)
		{
			if (game->map[x][y] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.player, y * game->twidth, x * game->theight);
			else if (game->map[x][y] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.exit, y * game->twidth, x * game->theight);
			else if (game->map[x][y] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.kebab, y * game->twidth, x * game->theight);
			else if (game->map[x][y] == 'X')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.pl_exit, y * game->twidth, x * game->theight);
			y++;
		}
		x++;
	}
}

void	print_background_walls(t_game *game)
{
	int	x;
	int	y;

	x = 0;
	while (x < game->nb_lines)
	{
		y = 0;
		while (y < game->nb_col)
		{
			if (game->map[x][y] == '1')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.wall, y * game->twidth, x * game->theight);
			else
				mlx_put_image_to_window(game->mlx, game->win, \
				game->sprite.bg, y * game->twidth, x * game->theight);
			y++;
		}
		x++;
	}
}

int	store_sprite(t_game *game)
{
	game->sprite.bg = mlx_xpm_file_to_image(game->mlx, \
	"textures/background-resized.xpm", &game->twidth, &game->theight);
	if (game->sprite.bg == NULL)
		return (1);
	game->sprite.kebab = mlx_xpm_file_to_image(game->mlx, \
	"textures/kebab.xpm", &game->twidth, &game->theight);
	if (game->sprite.kebab == NULL)
		return (1);
	game->sprite.wall = mlx_xpm_file_to_image(game->mlx, \
	"textures/wall2.xpm", &game->twidth, &game->theight);
	if (game->sprite.wall == NULL)
		return (1);
	game->sprite.player = mlx_xpm_file_to_image(game->mlx, \
	"textures/hipster.xpm", &game->twidth, &game->theight);
	if (game->sprite.player == NULL)
		return (1);
	game->sprite.exit = mlx_xpm_file_to_image(game->mlx, \
	"textures/door.xpm", &game->twidth, &game->theight);
	if (game->sprite.exit == NULL)
		return (1);
	game->sprite.pl_exit = mlx_xpm_file_to_image(game->mlx, \
	"textures/hipster-exit.xpm", &game->twidth, &game->theight);
	if (game->sprite.pl_exit == NULL)
		return (1);
	return (0);
}

void	render_game(t_game *game)
{
	print_background_walls(game);
	print_collectibles_player_exit(game);
}
