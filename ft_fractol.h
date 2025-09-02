#ifndef FT_FRACTOL_H
# define FT_FRACTOL_H

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include "minilibx-linux/mlx.h"

#define WIDTH 800
#define HEIGHT 800

#define BLACK       0x000000
#define WHITE       0xFFFFFF
#define RED         0xFF0000
#define GREEN       0x00FF00
#define BLUE        0x0000FF
#define YELLOW      0xFFFF00
#define MAGENTA     0xFF00FF
#define CYAN        0x00FFFF

#define RIGHT	65363
#define LEFT	65361
#define UP		65362
#define DOWN	65364
#define ZOOM_IN 65451
#define ZOOM_OUT 65453

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
	double	escape_value;
	int		iteration;
	double		a;
	double		b;
	float		zomm_in;
	double		julia_r;
	double		julia_i;
	t_num		z;
	t_num		c;

}t_fractal;

int	ft_strncmp(const char *s1, const char *s2, size_t n);
void	ft_putstr_fd(char *s, int fd);
void draw(t_fractal *fractol);
void    event_init(t_fractal *farcatl);
int my_close(t_fractal *fractol);
int key(int keysym,t_fractal *fractol);

#endif