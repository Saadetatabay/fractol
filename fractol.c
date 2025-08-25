#include "ft_fractol.h"

double  scale(double num,double new_min,double new_max,double old_min,double old_max)
{
    return (((num - old_min)*(new_max - new_min) / (old_max - old_min)) + new_min);
}

// z = z^2 + c 
// z initally zeroo
void pixel(int x,int y,t_fractal *fractol)
{
    double  tem_real;
    t_num   z;
    t_num   c;

    z.real_x = 0;
    z.imaginary_y = 0;
    c.real_x = scale(x,-2,2,0,WIDTH);
    c.imaginary_y = scale(y,2,-2,0,HEIGHT);
    tem_real = (z.real_x * z.real_x) - (z.imaginary_y * z.imaginary_y);
    z.imaginary_y = 2 * z.imaginary_y * z.real_x;
    z.real_x = tem_real;
    z.imaginary_y += c.imaginary_y;
    z.real_x += z.real_x;
}

int main(int arg,char *argv[])
{
    int     x;
    int     y;
    t_fractal fractol;

    y = 0;
    if ((arg == 2 && !ft_strncmp(argv[1],"mandelbrot",10)) || (arg == 4 && !ft_strncmp(argv[1],"julia",5)))
    {
        fractol.name = argv[1];
        fractol.mlx_conn = mlx_init();
        if(!fractol.mlx_conn)
        {
            printf("fail");
            return (1);
        }
        fractol.mlx_wind = mlx_new_window(fractol.mlx_conn,WIDTH,HEIGHT,fractol.name);
        if (!fractol.mlx_wind)
        {
            mlx_destroy_display(fractol.mlx_conn);
            free(fractol.mlx_conn);
            return (1);
        }
        fractol.img.img_ptr = mlx_new_image(fractol.mlx_conn,WIDTH,HEIGHT);
        if (!fractol.img.img_ptr)
        {
            mlx_destroy_window(fractol.mlx_conn,fractol.mlx_wind);
            mlx_destroy_display(fractol.mlx_conn);
        }
        fractol.img.pix_ptr = mlx_get_data_addr(fractol.img.img_ptr,&fractol.img.bit,&fractol.img.line,&fractol.img.endian);
        
        while (y < HEIGHT)
        {
            while (x < WIDTH)
            {
                x = 0;
                pixel(x,y,&fractol);
                x++;
            }
            y++;
        }
    }
    else
        return (1);
}