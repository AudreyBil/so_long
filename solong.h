/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solong.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abillote <abillote@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 16:39:11 by abillote          #+#    #+#             */
/*   Updated: 2024/01/25 15:41:26 by abillote         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SOLONG_H
# define SOLONG_H

# include <mlx.h>
# include "libft/libft.h"
# include <stdio.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define TILE_WIDTH	64
# define TILE_HEIGHT	64

//Sprites/Textures

typedef struct s_sprite {
	void	*kebab;
	void	*player;
	void	*bg;
	void	*wall;
	void	*exit;
	void	*pl_exit;
}				t_sprite;

//Game structure
typedef struct s_game {
	void		*mlx;
	void		*win;
	char		**map;
	int			twidth;
	int			theight;
	int			nb_lines;
	int			nb_col;
	int			nb_kebab;
	int			player_x;
	int			player_y;
	int			check_nb_keb;
	int			check_nb_exit;
	int			exit_x;
	int			exit_y;
	int			nb_keb_collected;
	t_sprite	sprite;
	int			game_over;
	int			mvm_count;
}				t_game;

//\render game functions
void	render_game(t_game *game);
void	print_mvm_count(t_game *game);
int		store_sprite(t_game *game);

//Map functions
void	read_map(char *file, t_game *game);
int		is_valid_map(t_game *game);
int		flood_fill(t_game *game);
void	player_position(t_game *game);
int		is_rectangle_walls_characters(t_game *game);
int		is_wall(int x, int y, t_game *game);

//Free functions
void	free_map(t_game *game);
void	free_visited(int **visited, int nb_lines);

#endif
