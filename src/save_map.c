/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 11:37:30 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 17:09:16 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

void	check_map_size(int lines, int cols, t_game *game)
{
	if (lines > MAX_LINES || cols > MAX_COLS)
		print_error("Error\nMap too big.", game, 0);
}

void	save_coordinates(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->map->lines)
	{
		j = 0;
		while (j < game->map->cols)
		{
			if (game->map->grid[i][j] == 'P')
			{
				game->player_x = j;
				game->player_y = i;
			}
			if (game->map->grid[i][j] == 'E')
			{
				game->exit_x = j;
				game->exit_y = i;
			}
			j++;
		}
		i++;
	}
}

void	save_line(t_game *game, char *line, int i_line, int fd)
{
	game->map->grid[i_line] = ft_calloc(game->map->cols + 1, sizeof(char));
	if (!game->map->grid[i_line])
		return (map_error("Error\nCould not allocate memory.", \
			game, i_line, fd), free(line));
	else
		ft_strcpy(game->map->grid[i_line], line);
	free(line);
}

int	check_line_size(t_game *game, char *line, int i_line, int fd)
{
	int	lines;
	int	cols;

	lines = game->map->lines;
	cols = game->map->cols;
	if ((i_line == lines - 1) && ((line[cols - 1] == '\n') || \
		(line[cols - 1] == '\0' && line[cols - 2] == '1')))
		return (1);
	else if (line[cols -1] == '\n')
		return (1);
	else
	{
		map_error("Error\nMap: Wrong line size.", game, i_line, fd);
		return (0);
	}
}

void	save_map(t_game *game, char *file_name)
{
	int		fd;
	int		i_line;
	char	*line;

	fd = open(file_name, O_RDONLY);
	game->map->grid = ft_calloc(game->map->lines, sizeof(char *));
	if (!game->map->grid)
		print_error("Error\nCould not allocate memory.", game, 1);
	i_line = 0;
	while (i_line < game->map->lines)
	{
		line = get_next_line(fd);
		if (!line)
		{
			map_error("Error\nCould not allocate memory.", \
				game, i_line, fd);
			free(line);
			return ;
		}
		if (check_line_size(game, line, i_line, fd))
			save_line(game, line, i_line, fd);
		i_line++;
	}
	close(fd);
	check_map_symbols(game);
}
