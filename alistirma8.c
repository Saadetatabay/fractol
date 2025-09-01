#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define HEIGHT 400
#define WIDTH 400

typedef struct s_img
{
    void    *img_ptr; //image için yer ayırdığımız 
    char    *img_pixel_ptr;
    int     bits_per_pixel;
    int     endian;
    int     line_len;
}t_img;


typedef struct s_var{
    void    *mlx_con;
    void    *mlx_win;
    t_img   img;
}t_var;
int colour_screen(t_var *t_data,int colour)
{
    int pixel_address;
    for(int y = 0;y<WIDTH;y++)
    {
        for(int x = 0;x<HEIGHT;x++)
        {
            pixel_address = (y * t_data->img.line_len) + (x*(t_data->img.bits_per_pixel/8));
            //hafızada her pikselin 4 baytı vardı pixel_adress pikselin başlangıç adresi 
            t_data->img.img_pixel_ptr[pixel_address + 0] = colour & 0xFF;          // mavi
            t_data->img.img_pixel_ptr[pixel_address + 1] = (colour >> 8) & 0xFF;   // yeşil
            t_data->img.img_pixel_ptr[pixel_address + 2] = 0xFF ;//(colour >> 16) & 0xFF;  // kırmızı
            t_data->img.img_pixel_ptr[pixel_address + 3] = 0;        
        }
    }
    mlx_put_image_to_window(t_data->mlx_con, t_data->mlx_win,t_data->img.img_ptr, 0, 0);

}
int f(int keysym,t_var *data)
{
    if(keysym ==65307)
    {
        mlx_destroy_window(data->mlx_con,data->mlx_win);
        mlx_destroy_display(data->mlx_con);
        free(data->mlx_con);
        return (1);
    }
    else if (keysym == 114)
        colour_screen(data,0xFF0000);
    else if (keysym == 103)
        colour_screen(data,0x00FF00);
    else if (keysym == 98)
        colour_screen(data, 0x0000FF);

    return (0);
}

int main()
{   
    t_var   t_data;
    t_data.mlx_con = mlx_init();
    if(!t_data.mlx_con)
    {
        printf("fail");
        return (1);
    }
    t_data.mlx_win = mlx_new_window(t_data.mlx_con, WIDTH,HEIGHT,"window");
    if(!t_data.mlx_win)
    {
        mlx_destroy_display(t_data.mlx_con);
        free(t_data.mlx_con);
    }
    t_data.img.img_ptr = mlx_new_image(t_data.mlx_con,WIDTH,HEIGHT);

    //img_pixel_ptr resmin hafızadaki başlangıç adresi
    t_data.img.img_pixel_ptr = mlx_get_data_addr(t_data.img.img_ptr,&t_data.img.bits_per_pixel,&t_data.img.line_len,&t_data.img.endian);
    mlx_hook(t_data.mlx_win,2,1L<<0,f,&t_data);
    mlx_loop(t_data.mlx_con);
}