/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:29:23 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:05:13 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

void	load_images(t_game *game)
{
	int	width;
	int	height;

	game->images = ft_calloc(1, sizeof(t_images));
	if (!game->images)
		print_error("Error\nCould not allocate memory.", game, 1);
	game->images->background = \
		mlx_xpm_file_to_image(game->mlx, "img/floor.xpm", &width, &height);
	game->images->player_right = \
		mlx_xpm_file_to_image(game->mlx, "img/player_right.xpm", \
			&width, &height);
	game->images->player_left = \
		mlx_xpm_file_to_image(game->mlx, "img/player_left.xpm", \
			&width, &height);
	game->images->wall = \
		mlx_xpm_file_to_image(game->mlx, "img/wall.xpm", &width, &height);
	game->images->exit = \
		mlx_xpm_file_to_image(game->mlx, "img/exit.xpm", &width, &height);
	game->images->collectable = \
		mlx_xpm_file_to_image(game->mlx, "img/collectable.xpm", \
				&width, &height);
	if (game->images->background == 0 || game->images->player_right == 0 || \
		game->images->wall == 0 || game->images->exit == 0 || \
			game->images->collectable == 0)
		print_error("Error\nFailed to load .xpm files.", game, 1);
}

void	draw_sprites(t_game *game)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map->lines)
	{
		x = 0;
		while (x < game->map->cols - 1)
		{
			if (game->map->grid[y][x] == 'P')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->images->player_right, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == '1')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->images->wall, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == 'E')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->images->exit, x * TILE_SIZE, y * TILE_SIZE);
			else if (game->map->grid[y][x] == 'C')
				mlx_put_image_to_window(game->mlx, game->win, \
				game->images->collectable, x * TILE_SIZE, y * TILE_SIZE);
			x++;
		}
		y++;
	}
}

void	draw_background(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map->lines)
	{
		x = 0;
		while (x < game->map->cols - 1)
		{
			mlx_put_image_to_window(game->mlx, game->win, \
				game->images->background, x, y);
			x += 1 * TILE_SIZE;
		}
		y += 1 * TILE_SIZE;
	}
}

void	start_game(t_game *game)
{
	int	width;
	int	height;

	game->mlx = mlx_init();
	if (!game->mlx)
		print_error("Error\nMLX failed to launch.", game, 1);
	game->mlx_init = 1;
	load_images(game);
	game->images_created = 1;
	width = TILE_SIZE * (game->map->cols - 1);
	height = TILE_SIZE * (game->map->lines);
	game->win = mlx_new_window(game->mlx, width, height, "lgandari's Pacman");
	if (!game->win)
		print_error("Error\nWindow failed to launch.", game, 1);
	game->win_init = 1;
	game->n_collectables = 0;
	draw_background(game);
	draw_sprites(game);
}
