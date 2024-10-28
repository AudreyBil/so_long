/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 14:07:55 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 15:44:15 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "solong.h"

void	check_new_position(t_game *game)
{
	if (game->map[game->player_x][game->player_y] == 'C')
	{
		game->nb_keb_collected++;
		game->map[game->player_x][game->player_y] = '0';
	}
	if (game->map[game->player_x][game->player_y] == 'E' \
	&& game->nb_keb_collected == game->nb_kebab)
	{
		ft_printf("Congratulations, you collected all the Döners ! \
		\n Score : %d\n", game->mvm_count);
		game->game_over = 1;
	}
	if (game->map[game->player_x][game->player_y] == 'E' \
	&& game->nb_keb_collected != game->nb_kebab)
	{
		ft_printf("You need to collect all the Döners !\n");
		game->map[game->player_x][game->player_y] = 'X';
	}
	else
		game->map[game->player_x][game->player_y] = 'P';
}

void	move_player(int keycode, t_game *game)
{
	if (keycode == 119 && \
	is_wall(game->player_x - 1, game->player_y, game) == 0)
	{
		game->player_x--;
		print_mvm_count(game);
	}
	if (keycode == 97 && \
	is_wall(game->player_x, game->player_y - 1, game) == 0)
	{
		game->player_y--;
		print_mvm_count(game);
	}
	if (keycode == 115 && \
	is_wall(game->player_x + 1, game->player_y, game) == 0)
	{
		game->player_x++;
		print_mvm_count(game);
	}
	if (keycode == 100 && \
	is_wall(game->player_x, game->player_y + 1, game) == 0)
	{
		game->player_y++;
		print_mvm_count(game);
	}
}

int	end_game(t_game *game)
{
	ft_printf("\n-- Game ended --\n");
	free_map(game);
	mlx_destroy_image(game->mlx, game->sprite.bg);
	mlx_destroy_image(game->mlx, game->sprite.wall);
	mlx_destroy_image(game->mlx, game->sprite.player);
	mlx_destroy_image(game->mlx, game->sprite.pl_exit);
	mlx_destroy_image(game->mlx, game->sprite.exit);
	mlx_destroy_image(game->mlx, game->sprite.kebab);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit (0);
	return (0);
}

int	key_handler(int keycode, t_game *game)
{
	if (keycode == 65307)
		end_game(game);
	if ((keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100) \
	&& game->game_over == 0)
	{
		if (game->map[game->player_x][game->player_y] != 'E' \
		&& game->map[game->player_x][game->player_y] != 'X')
			game->map[game->player_x][game->player_y] = '0';
		if (game->map[game->player_x][game->player_y] == 'X')
			game->map[game->player_x][game->player_y] = 'E';
		move_player(keycode, game);
		check_new_position(game);
		render_game(game);
		if (game->game_over == 1)
		{
			end_game(game);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	game.game_over = 0;
	game.mvm_count = 0;
	game.nb_keb_collected = 0;
	if (argc == 2)
	{
		read_map(argv[1], &game);
		game.twidth = 32;
		game.theight = 32;
		game.mlx = mlx_init();
		game.win = mlx_new_window(game.mlx, game.nb_col * game.twidth, \
		game.nb_lines * game.theight, "so_long");
		if (store_sprite(&game) == 1)
			ft_printf("Error\n Loading the images");
		render_game(&game);
		mlx_hook(game.win, 17, 0L, end_game, &game);
		mlx_key_hook(game.win, key_handler, &game);
		mlx_loop(game.mlx);
	}
	else
		ft_printf("\n--Error--\nWrong number of arguments\n\n");
	exit(EXIT_SUCCESS);
}
