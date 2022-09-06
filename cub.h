/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamian <amamian@student.42yerevan.am>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 21:46:42 by kshegunt          #+#    #+#             */
/*   Updated: 2022/06/06 22:41:18 by amamian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include "libft/libft.h"
# include "mlx/mlx.h"

/*
 * width and height are only used for textures (no, so, we, ea)
 * they are not used for the intermediary image (cur_img)
 */
typedef struct s_img
{
	void	*img;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		w;
	int		h;
	char	*img_addr;
}	t_img;

/*
 * m -- a matrix for the map
 */
typedef struct s_info
{
	t_img	no;
	t_img	so;
	t_img	we;
	t_img	ea;
	char	*no_t;
	char	*so_t;
	char	*we_t;
	char	*ea_t;
	int		floor_c[3];
	int		ceil_c[3];
	double	x_cur;
	double	y_cur;
	double	x_dir;
	double	y_dir;
	double	x_plane;
	double	y_plane;
	char	**m;
	void	*mlx;
	void	*win;
	t_img	cur_img;
	t_img	*cur_t;
	int		mapx;
	int		mapy;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	double	perpwalldist;
	double	wallx;
	int		stepx;
	int		stepy;
	int		side;
	int		up;
	int		down;
	int		left;
	int		right;
	double	texpos;
	double	texstep;
	double	olddirx;
	double	oldplanex;
	char	*dst;
	int		i;
	int		mask;
}	t_info;

# define MISCONFIG_MSG "Error\n"
# define ELEM_MASK 0b00111111
# define NORTH_MASK 0b00000001
# define SOUTH_MASK 0b00000010
# define WEST_MASK 0b00000100
# define EAST_MASK 0b00001000
# define FLOOR_MASK 0b00010000
# define CEIL_MASK 0b00100000
# define RGB_CNT 3
# define ELEM_DELIM ' '
# define COLOR_DELIM ','
# define EMP_SPC '0'
# define WALL '1'
# define START_N 'N'
# define START_S 'S'
# define START_E 'E'
# define START_W 'W'
# define NORTH_T "NO"
# define SOUTH_T "SO"
# define WEST_T "WE"
# define EAST_T "EA"
# define FLOOR_C "F"
# define CEIL_C "C"
# define PXL_SIZE 30
# define PLANE_X 0.0
# define PLANE_Y 0.66
# define MOVE_SPEED 0.1
# define ROT_SPEED 0.1
# define MLX_ESC 53 
# define MLX_UP_1 13 
# define MLX_UP_2 126
# define MLX_DOWN_1 1
# define MLX_DOWN_2 125
# define MLX_LEFT_1 0
# define MLX_LEFT_2 123
# define MLX_RIGHT_1 2
# define MLX_RIGHT_2 124
# define MLX_PRESSED 2
# define MLX_RELEASED 3
# define MLX_DESTROYED 17
# define MLX_DEFAULT_MASK 0
# define WIN_HEIGHT 1000
# define WIN_WIDTH 1000
# define ERR_NO "Error\nWasn't able to process NO texture\n"
# define ERR_SO "Error\nWasn't able to process SO texture\n"
# define ERR_WE "Error\nWasn't able to process WE texture\n"
# define ERR_EA "Error\nWasn't able to process EA texture\n"

void	process_input(int argc, char **argv, t_info *m);
t_list	*extract_input_lines(int fd);
char	**construct_map(t_list *lines);
t_list	*construct_elements(t_list *lines, t_info *m, int mask);
void	error_exit(char *s, int status);
int		ft_arrlen(char **a);
void	delete_line(void *p);
void	skip_line(void *p);
void	ft_arrfree(char **a);
int		validate_input(t_info *m);
int		partofmap(char c);
int		nonwall_partofmap(char c);
int		init_textures(t_info *m);
void	dda(t_info *m);
int		key_hook(int keycode, t_info *m);
int		win_destroy(void);
void	init_press(t_info *m);
int		key_pressed(int keycode, t_info *m);
int		key_released(int keycode, t_info *m);
int		render_next_frame(t_info *m);
void	init_press(t_info *m);
void	drawline(double perpwalldist, int x, t_info *m);

#endif
