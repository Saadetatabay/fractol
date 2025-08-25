#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"

#define WIDTH 800
#define HEIGHT 800

typedef struct s_num
{
	double	real_x;
	double	imaginary_y;
}t_num;

typedef struct s_img{
	void	*img_ptr;
	char	*pix_ptr;
	int		line;
	int		endian;
	int		bit;
}t_img;

typedef struct s_fractol{
    void	*mlx_conn;
	void	*mlx_wind;
	t_img	img;
	char	*name;
}t_fractal;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
#endif