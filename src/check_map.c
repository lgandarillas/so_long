/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:55:01 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:04:01 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

void	check_valid_symbols(t_game *game)
{
	int			i;
	int			j;
	char		symbol;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->cols)
		{
			symbol = game->map->grid[i][j];
			if (symbol != '0' && symbol != '1' && symbol != 'E' && \
				symbol != 'C' && symbol != 'P' && symbol != '\n' && \
					symbol != '\0')
				print_error("Error\nInvalid symbol.", game, 1);
			j++;
		}
		i++;
	}
}

void	check_walls(t_game *game)
{
	int		i;

	i = 0;
	while (i < game->map->cols - 1)
	{
		if (game->map->grid[0][i] != '1' || \
			game->map->grid[game->map->lines - 1][i] != '1')
			print_error("Error\nIncorrect map walls.", game, 1);
		i++;
	}
	i = 0;
	while (i < game->map->lines)
	{
		if (game->map->grid[i][0] != '1' || \
			game->map->grid[i][game->map->cols - 2] != '1')
			print_error("Error\nIncorrect map walls.", game, 1);
		i++;
	}
}

void	check_num_symbols(t_game *game)
{
	int	i;
	int	j;

	game->map->n_collectables = 0;
	game->map->n_player = 0;
	game->map->n_exit = 0;
	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->grid[i][j] == 'P')
				game->map->n_player++;
			if (game->map->grid[i][j] == 'E')
				game->map->n_exit++;
			if (game->map->grid[i][j] == 'C')
				game->map->n_collectables++;
			j++;
		}
		i++;
	}
	if (game->map->n_collectables < 1 || game->map->n_player != 1 \
			|| game->map->n_exit != 1)
		print_error("Error\nMap Error!.", game, 1);
}

void	check_map_symbols(t_game *game)
{
	check_walls(game);
	check_valid_symbols(game);
	check_num_symbols(game);
	save_coordinates(game);
	game->num_moves = 0;
	check_map_path(game);
}

void	map_checker(char *file_name, t_game *game)
{
	int		fd;
	int		lines;
	char	*line;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error("Error\nFile could not be opened.", NULL, 0);
	game->map = ft_calloc(1, sizeof(t_map));
	if (!game->map)
		print_error("Error\nCould not allocate memory.", NULL, 0);
	lines = 0;
	line = get_next_line(fd);
	game->map->cols = ft_strlen(line);
	while (line != NULL)
	{
		lines++;
		free(line);
		line = get_next_line(fd);
	}
	game->map->lines = lines;
	close(fd);
	check_map_size(game->map->lines, game->map->cols, game);
	save_map(game, file_name);
}
