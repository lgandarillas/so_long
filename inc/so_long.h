/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:28:16 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:38:36 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "mlx/mlx.h"
# include "libft_v2/inc/libft.h"
# include "libft_v2/inc/get_next_line.h"
# include "libft_v2/inc/ft_printf.h"

# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

# define KEY_ESC		53
# define KEY_W			13
# define KEY_A			0
# define KEY_S			1
# define KEY_D			2
# define ARROW_UP		126
# define ARROW_DOWN		125
# define ARROW_LEFT		123
# define ARROW_RIGHT	124

# define TILE_SIZE	32

# define MAX_LINES	30
# define MAX_COLS	80

typedef struct s_images
{
	void	*background;
	void	*wall;
	void	*player_right;
	void	*player_left;
	void	*exit;
	void	*collectable;
}				t_images;

typedef struct s_map
{
	char	**grid;
	int		n_collectables;
	int		n_exit;
	int		n_player;
	int		lines;
	int		cols;
}				t_map;

typedef struct s_track_map
{
	char	**grid;
	int		n_collectables;
	int		n_exit;
}				t_track_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_images	*images;
	t_track_map	*track_map;
	int			map_created;
	int			images_created;
	int			mlx_init;
	int			win_init;
	int			num_moves;
	int			n_collectables;
	int			player_x;
	int			player_y;
	int			exit_x;
	int			exit_y;
}				t_game;

void	print_error(char *message, t_game *game, int clean_game);
void	game_error(t_game *game, char *msg);
void	map_error(char *message, t_game *game, int i, int fd);
void	check_map_size(int lines, int cols, t_game *game);

void	start_game(t_game *game);
void	move(t_game *game, int shift_x, int shift_y);
int		close_window(t_game *game);
int		check_key_pressed(int key, t_game *game);
void	save_coordinates(t_game *game);

void	save_map(t_game *game, char *file_name);
void	map_checker(char *filename, t_game *game);
void	check_map_path(t_game *game);
void	check_map_symbols(t_game *game);

#endif
