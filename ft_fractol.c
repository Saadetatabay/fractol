#include "ft_fractol.h"
#include <stdio.h>

double  scale(double num,double new_min,double new_max,double old_min,double old_max)
{
    return (((num - old_min)*(new_max - new_min) / (old_max - old_min)) + new_min);
}

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
    t_num   z;
    t_num   c;
	
	z.real_x = 0; //başlangıçta 0
	z.imaginary_y = 0; //başlangıçta 0
	c.real_x = scale(x,-2,2,0,WIDTH) + fractol->a; //-2 2 arasına scale ettik
	c.imaginary_y = scale(y,2,-2,0,HEIGHT) + fractol->b; //-2 ile 2 arasına scale ettik
    i = 0;
    while (i < fractol->iteration)
    {
        tem_real = (z.real_x * z.real_x) - (z.imaginary_y * z.imaginary_y); //real kısım
        z.imaginary_y = 2 * z.imaginary_y * z.real_x; 
        z.real_x = tem_real + c.real_x;
        z.imaginary_y += c.imaginary_y;
        if ((z.real_x * z.real_x) + (z.imaginary_y * z.imaginary_y) > fractol->escape_value)
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

int key(int keysym,t_fractal *fractol)
{
    if(keysym ==65307)
    {
        mlx_destroy_window(fractol->mlx_conn,fractol->mlx_wind);
        mlx_destroy_display(fractol->mlx_conn);
        free(fractol->mlx_conn);
        return (1);
    }
    else if (keysym == RIGHT)
    {
        printf("right");
        fractol->a += 0.5;
    }
    else if (keysym == LEFT)
    {
        printf("left");
        fractol->a += -0.5;
    }
        else if (keysym == LEFT)
    {
        printf("left");
        fractol->a += -0.5;
    }
        else if (keysym == UP)
    {
        printf("up");
        fractol->b += 0.5;
    }

    else if (keysym == DOWN)
    {
        printf("down");
        fractol->b -= 0.5;
    }
    draw(fractol);
    return (0);
}


int my_close(t_fractal *fractol)
{
    mlx_destroy_window(fractol->mlx_conn, fractol->mlx_wind);
    mlx_destroy_display(fractol->mlx_conn);
    free(fractol->mlx_conn);
    exit(0);
    return (0);
}
void    event_init(t_fractal *farcatl)
{
    mlx_hook(farcatl->mlx_wind,2,1L<<0,key,farcatl); //keypress
    //mlx_hook(farcatl->mlx_wind,4,1L<<2,mouse,farcatl); //button press
    mlx_hook(farcatl->mlx_wind,17,1L<<17,my_close,farcatl); //destroy notify
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

int main(int arg,char *argv[])
{
    t_fractal fractol;
    fractol.a = 0.0;
    fractol.b=0.0;
    if ((arg == 2 && !ft_strncmp(argv[1],"mandelbrot",10)) || (arg == 4 && !ft_strncmp(argv[1],"julia",5)))
    {
        fractol.name = argv[1];
        fractol.mlx_conn = mlx_init(); //kütüp ile bağlantı
        if(!fractol.mlx_conn) //bağlantı yapıldı mı kontrol ettim
        {
            printf("fail");
            return (1);
        }
        fractol.mlx_wind = mlx_new_window(fractol.mlx_conn,WIDTH,HEIGHT,fractol.name);//pencere açtıö
        if (!fractol.mlx_wind)
        {
            mlx_destroy_display(fractol.mlx_conn);
            free(fractol.mlx_conn);
            return (1);
        }
        fractol.img.img_ptr = mlx_new_image(fractol.mlx_conn,WIDTH,HEIGHT); //buff image 
        if (!fractol.img.img_ptr)
        {
            mlx_destroy_window(fractol.mlx_conn,fractol.mlx_wind);
            mlx_destroy_display(fractol.mlx_conn);
        }
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