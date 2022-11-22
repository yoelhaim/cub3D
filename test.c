#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct s_mlx {
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;
 



int	key_hook(int keycode, t_mlx *mlx)
{ 
	time_t t;
	static int r;
	srand((unsigned) time(&t));
	if (keycode == 126)
		  mlx_pixel_put(mlx->mlx, mlx->mlx_win ,rand() % 900, 10, 0xF06292);
		r+=2;
	printf("Hello from key_hook! %d\n", keycode);
	return (0);
}

int main()
{
	t_mlx mlx;

	mlx.mlx = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx, 900, 600, "Game");
	mlx.img = mlx_new_image(mlx.mlx, 900, 600);
	mlx.addr = mlx_get_data_addr(mlx.img, &mlx.bits_per_pixel, &mlx.line_length,&mlx.endian);

	int i =0;
	while(i < 900)
	{
	  mlx_pixel_put(mlx.mlx, mlx.mlx_win ,i, 600/2, 0xF06292);
	 
		i++;
	}
	mlx_pixel_put(mlx.mlx, mlx.mlx_win ,900, 600, 0xF06292);
  	mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
	mlx_string_put(mlx.mlx, mlx.mlx_win , 450, 300, 0xF06292, "oooh cheat");
  mlx_pixel_put(mlx.mlx, mlx.mlx_win ,10, 10, 0xF06292);
	// mlx_put_image_to_window(&mlx.mlx, &mlx.mlx_win, &mlx.img, 0, 0);
	mlx_loop(mlx.mlx);
}