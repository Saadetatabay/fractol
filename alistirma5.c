#include "minilibx-linux/mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>

#define WIDTH	400
#define HEIGHT	400

typedef struct my_data{
    void    *mlx_conn; //kütüp ile bağlantı
    void    *mlx_window; //window pointerı
    int     colour;
}tdata;

int key(int keysym,tdata *mydata)
{
        if (keysym == 65307) //esc
    {
        printf("ESC bastim");
        mlx_destroy_window(mydata->mlx_conn,mydata->mlx_window); //data struct pointerı old için -> ile ulaştık
        mlx_destroy_display(mydata->mlx_conn);
        free(mydata->mlx_conn);
        exit(0);
    }
    printf("pressed %d",keysym);
    sleep(1);
    return (1);
}

int change_colour(tdata *mydata)
{
    mlx_clear_window(mydata->mlx_conn,mydata->mlx_window); //pencerenin içini temizler
    mlx_string_put(mydata->mlx_conn,mydata->mlx_window,150,150,mydata->colour,"saadet ayseyi seviyor");
    if(mydata->colour == 0XFF0000)
        mydata->colour = 0x00FF00;//gren yaptık
    else if(mydata->colour == 0X00FF00)
        mydata->colour = 0x0000FF;//mavi yaptık
    else
        mydata->colour = 0xFF0000; //kırmızı yaptık
    return (0);
}

int main()
{
        tdata   data;
    
    data.mlx_conn = mlx_init(); //kütüp ile bağlantı
    if(!data.mlx_conn)
    {
        printf("fail");
    }
    data.mlx_window=mlx_new_window(data.mlx_conn,WIDTH,HEIGHT,"window"); //window pointerı
    if(!data.mlx_window)
    {
        mlx_destroy_display(data.mlx_conn);
        free(data.mlx_conn);
    }
    data.colour = 0XFF0000; //kırmızı

    mlx_hook(data.mlx_window, 2, 1L<<0, key, &data); 

    mlx_loop_hook(data.mlx_conn,change_colour,&data);
    mlx_loop(data.mlx_conn);
}