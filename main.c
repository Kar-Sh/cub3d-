/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamian <amamian@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 00:35:24 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 21:43:24 by amamian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#include "mlx/mlx.h"

int	main(int argc, char	**argv)
{
	t_info	m;

	process_input(argc, argv, &m);
	if (!validate_input(&m))
		error_exit("Error\nInvalid map\n", EXIT_FAILURE);
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WIN_WIDTH, WIN_HEIGHT, "test");
	init_textures(&m);
	dda(&m);
	init_press(&m);
	mlx_hook(m.win, MLX_PRESSED, 1L << 0, key_pressed, &m);
	mlx_hook(m.win, MLX_RELEASED, 1L << 1, key_released, &m);
	mlx_hook(m.win, MLX_DESTROYED, 1L << 17, win_destroy, NULL);
	mlx_loop_hook(m.mlx, render_next_frame, &m);
	mlx_loop(m.mlx);
	return (0);
}
