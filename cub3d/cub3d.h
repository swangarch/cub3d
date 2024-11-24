/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shuwang <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:49:35 by shuwang           #+#    #+#             */
/*   Updated: 2024/11/22 14:49:36 by shuwang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdio.h>
# include <sys/time.h>
# include "libft.h"
# include "mlx.h"


/*SCREEN*/
# define SCREEN_HEIGHT 768
# define SCREEN_WIDTH 1024

/*SAMPLE PARAM*/
# define SCALE 500.0
# define SCALE_SCREEN 150.0
# define STEP 0.02
# define STEP_ANGLE 1.0
# define STEP_ANGLE_MOUSE 3.0
# define STEP_HEIGHT_RATIO 0.05
# define SAMPLE 600
# define FOV 60.0
# define BOX_SIZE 50.0
# define GRID_SIZE 1

/*COLORS*/
# define GREEN -16711936
# define RED -65536
# define BLUE -16776961
# define YELLOW -256
# define WHITE -1
# define CYAN -16711681
# define MAGENTA -65281

/*KEY CONTROL*/
# define ESC 65307
# define D 100
# define A 97
# define W 115
# define S 119
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

/*ORIENTATION*/
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define NOT_ONBOX 0

/*DOUBLE ERROR*/
# define MIN_ERR 0.000000000001
# define MIN_ERR2 0.0

/*RENDER ON THE SCREEN*/
# define POSITION_X 500
# define DISPLAY_W 500.0
# define DISPLAY_H 300.0
# define POSITION_Y 300
# define NUMM 100


# define TIME_ITVAL_MOUSE 10000

typedef struct s_vector
{
    double         x;
    double         y;
}	t_vector;

typedef struct s_vars
{
    t_vector    ray[(int)SAMPLE + 1];
    int         ray_color[(int)SAMPLE + 1];
    t_vector    posv;
    t_vector    dirv;

    t_vector    last_mouse_pos;
    double      height_ratio;

    time_t      last_mouse_move_t;

	void		*mlx;
	void		*win;
	char		(*map)[9];

    char        *buf_img;
    void        *buf_img_ptr;
    int         bits_per_pixel;
    int         size_line;
    int         endian;
}	t_vars;

/*MATH*/
double to_radians(double angle);
double ft_abs(double num);
int double_eql(double a, double b);
double len_2pt(double x1, double y1, double x2, double y2);

/*DRAW GEOMETRY*/
void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color);
void draw_box(t_vars *vars, double x, double y, double size);

/*GAME CONTROL*/
int	move_character(int keycode, t_vars *vars);
int	key_control(int keycode, t_vars *vars);
int mouse_move(int x, int y, t_vars *vars);

/*VECTOR*/

void normalize_vector(t_vector *vector, double scale);
void rotate_vector(t_vector *v, t_vector *vo, double radians);
double wall_distance(t_vars *vars, t_vector *vector, int *color, int i);
double vector_magnitude(t_vector *v);

/*RENDER*/
void    render_game(t_vars *vars);
void clear_image_buf(t_vars *vars);

/*COLOR*/
int create_trgb(int t, int r, int g, int b);

/*UTILS*/
time_t  get_current_time(void);

#endif