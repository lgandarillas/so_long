/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:29:08 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:16:44 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

int	close_window(t_game *game)
{
	game_error(game, "MLX Window Closed");
	return (0);
}

void	print_error(char *error_msg, t_game *game, int clean_game)
{
	ft_printf(error_msg);
	if (clean_game && game)
		game_error(game, "");
	exit(EXIT_FAILURE);
}

void	game_error(t_game *game, char *msg)
{
	int	i;

	ft_printf(msg);
	i = 0;
	while (i < game->map->lines)
	{
		free(game->map->grid[i]);
		i++;
	}
	free(game->map->grid);
	free(game->map);
	game->map = NULL;
	if (game->images_created == 1)
	{
		mlx_destroy_image(game->mlx, game->images->background);
		mlx_destroy_image(game->mlx, game->images->exit);
		mlx_destroy_image(game->mlx, game->images->collectable);
		mlx_destroy_image(game->mlx, game->images->player_right);
		mlx_destroy_image(game->mlx, game->images->wall);
		free(game->images);
	}
	if (game->win_init == 1 || game->mlx_init == 1)
		mlx_destroy_window(game->mlx, game->win);
	exit(EXIT_FAILURE);
}

void	map_error(char *message, t_game *game, int i_line, int fd)
{
	int	i;

	close(fd);
	i = 0;
	while (i < i_line)
	{
		free(game->map->grid[i]);
		i++;
	}
	free(game->map->grid);
	free(game->map);
	ft_printf(message);
	exit(EXIT_FAILURE);
}
