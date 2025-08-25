#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define HEIGHT 400
#define WIDTH 400
typedef struct sdata{
    void *my_con;
    void *my_win;
    int colour;
}tdata;
int colour_screen(tdata *data)
{
    for(int x = 0;x < WIDTH;x++)
    {
        for (int y = 0;y<HEIGHT;y++)
        {
            mlx_pixel_put(data->my_con, data->my_win, x, y, data->colour);
        }
    }
    return (0);
}
int key(int keysym,tdata *data)
{
    if(keysym ==65307)
    {
        mlx_destroy_window(data->my_con,data->my_win);
        mlx_destroy_display(data->my_con);
        free(data->my_con);
        return (1);
    }
    else if (keysym == 114)
        data->colour = 0xFF0000;
    else if (keysym == 103)
        data->colour = 0x00FF00;
    else if (keysym == 98)
        data->colour = 0x0000FF;

    colour_screen(data);
    return (0);
}

int main()
{
    tdata data;
    data.my_con = mlx_init();
    if(!data.my_con)
    {
        printf("fail");
        return (1);
    }
    data.my_win = mlx_new_window(data.my_con,WIDTH,HEIGHT,"window");
    if(!data.my_win)
    {
        mlx_destroy_display(data.my_con);
        free(data.my_con);
    }
    data.colour = 0xFFFFFF;
    mlx_hook(data.my_win,2,1L<<0,key,&data);
    mlx_loop(data.my_con);
}