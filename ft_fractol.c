/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: satabay <satabay@student.42istanbul.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/27 15:26:15 by satabay           #+#    #+#             */
/*   Updated: 2025/09/27 15:26:30 by satabay          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fractol.h"

static  void put_pixel(int x,int y,t_img *img,int colour)
{
    int	offset;
	offset = (y * img->line) + (x * (img->bit / 8));
    //unsigned int * kestleyerek bu adresi 4 baytlık integer gibi yorulatıyrouz
	*(unsigned int *)(img->pix_ptr + offset) = colour;
}

// z = z^2 + c 
// z initally zeroo
static void pixel(int x,int y,t_fractal *fractol)
{
    int     i;
    int     color;
    double  tem_real;

    i = 0;
	mandel_vs_julia(x,y,fractol);
    while (i < fractol->iteration)
    {
        tem_real = (fractol->z.real_x * fractol->z.real_x) - (fractol->z.imaginary_y * fractol->z.imaginary_y); //real kısım
        fractol->z.imaginary_y = 2 * fractol->z.imaginary_y * fractol->z.real_x; 
        fractol->z.real_x = tem_real + fractol->c.real_x;
        fractol->z.imaginary_y += fractol->c.imaginary_y;
        if ((fractol->z.real_x * fractol->z.real_x) + (fractol->z.imaginary_y * fractol->z.imaginary_y) > fractol->escape_value)
        {
            //mandelbrot değil
            //i değerini siyaj beyaz arasında bir renk yaptı
            color = scale(i,BLACK,WHITE,0,fractol->iteration); //kaç iterasyonda kaçtı hızlı mı yavaş mı
			put_pixel(x,y,&fractol->img,color);
            return ;
        }
        i++;
    }
	put_pixel(x,y,&fractol->img,MAGENTA);
    //mandelbrot set demek
}

void draw(t_fractal *fractol)
{
    int x;
    int y;
    y = 0;
    while (y < HEIGHT)
    {
			x = 0;
            while (x < WIDTH)
            {
                pixel(x,y,fractol);
                x++;
            }
            y++;
    }
	mlx_put_image_to_window(fractol->mlx_conn,fractol->mlx_wind,fractol->img.img_ptr,0,0);
}

void	fractol_init(t_fractal *fractol)
{
	    fractol->mlx_conn = mlx_init(); //kütüp ile bağlantı
        if(!fractol->mlx_conn) //bağlantı yapıldı mı kontrol ettim
        {
            printf("fail");
            return ;
        }
        fractol->mlx_wind = mlx_new_window(fractol->mlx_conn,WIDTH,HEIGHT,fractol->name);//pencere açtıö
        if (!fractol->mlx_wind)
        {
            mlx_destroy_display(fractol->mlx_conn);
            free(fractol->mlx_conn);
            return ;
        }
        fractol->img.img_ptr = mlx_new_image(fractol->mlx_conn,WIDTH,HEIGHT); //buff image 
        if (!fractol->img.img_ptr)
        {
            mlx_destroy_window(fractol->mlx_conn,fractol->mlx_wind);
            mlx_destroy_display(fractol->mlx_conn);
            free(fractol->mlx_conn);
        }
}

int main(int arg,char *argv[])
{
    t_fractal fractol;
    fractol.a = 0.0;
    fractol.b=0.0;
    fractol.zomm_in = 1.0;
    //(arg == 4 && !ft_strncmp(argv[1],"julia",5))
    if ((arg == 2 && !ft_strncmp(argv[1],"mandelbrot",10)) || (arg == 4 && !ft_strncmp(argv[1],"julia",5)))
    {
        fractol.name = argv[1];
		if (arg == 4)
		{
			fractol.julia_r = atof(argv[2]); //double yapıcam 
			fractol.julia_i = atof(argv[3]); //double yapıcam
		}
        fractol_init(&fractol);
        //pixel başlangıç adresi aldık
        fractol.img.pix_ptr = mlx_get_data_addr(fractol.img.img_ptr,&fractol.img.bit,&fractol.img.line,&fractol.img.endian);
        fractol.escape_value = 4; //iki yarıçaplı çember
        fractol.iteration = 150;
        draw(&fractol);
        event_init(&fractol);
		mlx_loop(fractol.mlx_conn);
    }
    else
        return (1);
}