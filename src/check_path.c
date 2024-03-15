/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:18:57 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/14 12:51:59 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

void	free_track_map(t_game *game, int lines)
{
	int	i;

	i = 0;
	while (i < lines)
	{
		free(game->track_map->grid[i]);
		i++;
	}
	free(game->track_map->grid);
	free(game->track_map);
	game->track_map = NULL;
}

void	create_track_map(t_game *game)
{
	int	i;

	game->track_map = ft_calloc(1, sizeof(t_track_map));
	if (!game->track_map)
		print_error("Error\nCould not allocate memory.\n\n", game, 1);
	game->track_map->grid = ft_calloc(1, game->map->lines * sizeof(int *));
	if (!game->track_map->grid)
		print_error("Error\nCould not allocate memory.\n\n", game, 1);
	game->track_map->n_collectables = game->map->n_collectables;
	game->track_map->n_exit = game->map->n_exit;
	i = 0;
	while (i < game->map->lines)
	{
		game->track_map->grid[i] = ft_calloc(game->map->cols, sizeof(int *));
		if (!game->track_map->grid[i])
		{
			free_track_map(game, i);
			print_error("Error\nCould not allocate memory.\n\n", game, 1);
		}
		i++;
	}
}

void	explore_track_map(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map->lines || x < 0 || x >= game->map->cols \
	|| game->map->grid[y][x] == '1' || game->track_map->grid[y][x])
		return ;
	game->track_map->grid[y][x] = 1;
	if (game->map->grid[y][x] == 'C')
		game->track_map->n_collectables--;
	if (game->map->grid[y][x] == 'E')
		game->track_map->n_exit--;
	explore_track_map(game, x + 1, y);
	explore_track_map(game, x - 1, y);
	explore_track_map(game, x, y + 1);
	explore_track_map(game, x, y - 1);
}

void	check_map_path(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	create_track_map(game);
	while (y < game->map->lines)
	{
		x = 0;
		while (x < game->map->cols)
		{
			if (game->map->grid[y][x] == 'P')
			{
				explore_track_map(game, x, y);
				if (game->track_map->n_collectables != 0 || \
						game->track_map->n_exit != 0)
					print_error("Error\nNo valid Path\n\n", game, 1);
			}
			x++;
		}
		y++;
	}
	free_track_map(game, y);
}
