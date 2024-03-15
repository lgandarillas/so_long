/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgandari <lgandari@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 16:29:43 by lgandari          #+#    #+#             */
/*   Updated: 2024/03/15 18:06:21 by lgandari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inc/so_long.h"

static int	check_extension(char *filename, char *extension)
{
	int	i;
	int	j;
	int	k;

	i = ft_strlen(filename) - ft_strlen(extension);
	j = 0;
	k = ft_strlen(filename);
	while (i < k)
	{
		if (filename[i] != extension[j])
			return (-1);
		i++;
		j++;
	}
	return (1);
}

int	check_key_pressed(int key, t_game *game)
{
	if (key == KEY_W || key == ARROW_UP)
		move(game, 0, -1);
	if (key == KEY_S || key == ARROW_DOWN)
		move(game, 0, 1);
	if (key == KEY_A || key == ARROW_LEFT)
		move(game, -1, 0);
	if (key == KEY_D || key == ARROW_RIGHT)
		move(game, 1, 0);
	if (key == KEY_ESC)
		game_error(game, "Window Closed.");
	return (0);
}

int	main(int argc, char **argv)
{
	t_game		*game;

	if (argc != 2)
		print_error("Error\nWrong arguments.", NULL, 0);
	if (check_extension(argv[1], ".ber") < 0)
		print_error("Error\nFile is not '.ber'.", NULL, 0);
	game = ft_calloc(1, sizeof(t_game));
	if (!game)
		print_error("Error\nCould not allocate memory.", NULL, 0);
	check_map(argv[1], game);
	start_game(game);
	mlx_key_hook(game->win, check_key_pressed, game);
	mlx_hook(game->win, 17, 0, close_window, game);
	mlx_loop(game->mlx);
}
