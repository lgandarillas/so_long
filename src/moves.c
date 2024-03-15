/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:30:26 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:08:56 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

char	get_position_symbol(t_game *game, int shift_x, int shift_y)
{
	int	next_x;
	int	next_y;

	next_x = game->player_x + shift_x;
	next_y = game->player_y + shift_y;
	return (game->map->grid[next_y][next_x]);
}

void	put_player(t_game *game, int shift_x, int shift_y)
{
	if (shift_x < 0)
	{
		mlx_put_image_to_window(game->mlx, game->win, \
			game->images->player_left,
			game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win, \
			game->images->player_right,
			game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
	}
}

void	move_player(t_game *game, int shift_x, int shift_y)
{
	if (game->exit_y != game->player_y || \
		game->exit_x != game->player_x)
	{
		mlx_put_image_to_window(game->mlx, game->win, \
		game->images->background, \
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
		game->map->grid[game->player_y][game->player_x] = '0';
	}
	else
	{
		mlx_put_image_to_window(game->mlx, game->win, game->images->exit, \
		game->player_x * TILE_SIZE, game->player_y * TILE_SIZE);
		game->map->grid[game->player_y][game->player_x] = 'E';
	}
	game->player_x += shift_x;
	game->player_y += shift_y;
	game->map->grid[game->player_y][game->player_x] = 'P';
	put_player(game, shift_x, shift_y);
}

void	move(t_game *game, int shift_x, int shift_y)
{
	char	next_symbol;

	next_symbol = get_position_symbol(game, shift_x, shift_y);
	if (next_symbol == '1')
		return ;
	if (next_symbol == '0' || next_symbol == 'C')
	{
		if (next_symbol == 'C')
			game->n_collectables++;
		move_player(game, shift_x, shift_y);
		game->num_moves++;
		ft_printf("Number of moves = %d\n", game->num_moves);
	}
	if (next_symbol == 'E')
	{
		move_player(game, shift_x, shift_y);
		game->num_moves++;
		ft_printf("Number of moves = %d\n", game->num_moves);
		if (game->n_collectables == game->map->n_collectables)
			game_error(game, "GAME OVER!");
	}
}
