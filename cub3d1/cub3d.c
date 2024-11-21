# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define SCREEN_HEIGHT 1024
# define SCREEN_WIDTH 768

# define SCALE 500.0
# define SCALE_SCREEN 150.0
# define STEP 0.02
# define STEP_ANGLE 1.0
# define SAMPLE 600.0
# define FOV 60.0
# define BOX_SIZE 50.0
# define GRID_SIZE 1

# define GREEN -16711936
# define RED -65536
# define BLUE -16776961
# define YELLOW -256
# define WHITE -1
# define CYAN -16711681
# define MAGENTA -65281

# define ESC 65307
# define D 100
# define A 97
# define W 115
# define S 119
# define LEFT 65361
# define RIGHT 65363

# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define NOT_ONBOX 0

double angle_radians(double angle)
{
    double radians;
    radians = angle * (M_PI / 180.0);
    return (radians);
}

typedef struct s_vars
{
    double         posx;
    double         posy;
    double         dirx;
    double         diry;
	void		*mlx;
	void		*win;
	char		(*map)[9];
    void *buf_img;
}	t_vars;

typedef struct s_vector
{
    double         x;
    double         y;
}	t_vector;

int create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void normalize_direction(t_vars *vars)
{
    double magnitude;

    magnitude = sqrt(vars->dirx * vars->dirx + vars->diry * vars->diry);
    vars->dirx /= magnitude;
    vars->diry /= magnitude;
    vars->dirx *= SCALE;
    vars->diry *= SCALE;
}

void normalize_direction_vector(t_vector *vector)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= SCALE;
    vector->y *= SCALE;
}

void normalize_vector(t_vector *vector, double scale)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= scale;
    vector->y *= scale;
}

void normalize_screen_vector(t_vector *vector)
{
    double magnitude;

    magnitude = sqrt(vector->x * vector->x + vector->y * vector->y);
    vector->x /= magnitude;
    vector->y /= magnitude;
    vector->x *= SCALE_SCREEN;
    vector->y *= SCALE_SCREEN;
}

double ft_abs(double num)
{
    if (num >= 0)
        return (num);
    else
        return (-num);
}

void draw_line(t_vars *vars, int x0, int y0, int x1, int y1, int color)
{
    int dx = ft_abs(x1 - x0);
    int dy = ft_abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1; // x方向的步进
    int sy = (y0 < y1) ? 1 : -1; // y方向的步进
    int err = dx - dy;           // 初始误差

    while (1) 
    {
        mlx_pixel_put((vars)->mlx, (vars)->win, x0, y0, color); // 绘制当前点
        if (x0 == x1 && y0 == y1) {
            break; // 到达终点
        }
        int e2 = 2 * err; // 误差两倍，用于判断步进方向
        if (e2 > -dy) {
            err -= dy; // 减去y的增量
            x0 += sx;  // x向前一步
        }
        if (e2 < dx) {
            err += dx; // 增加x的增量
            y0 += sy;  // y向前一步
        }
    }
}

void draw_box(t_vars *vars, double x, double y, double size)
{
    draw_line(vars, x - size / 2, y - size / 2, x + size / 2, y - size / 2, YELLOW);
    draw_line(vars, x - size / 2, y - size / 2, x - size / 2, y + size / 2, GREEN);
    draw_line(vars, x + size / 2, y + size / 2, x + size / 2, y - size / 2, MAGENTA);
    draw_line(vars, x + size / 2, y + size / 2, x - size / 2, y + size / 2, CYAN);
}

void rotate_vector(t_vars *vars, double radians)
{
    vars->dirx = vars->dirx * cos(radians) - vars->diry * sin(radians);
    vars->diry = vars->dirx * sin(radians) + vars->diry * cos(radians);
    normalize_direction(vars);
    return ;
}

// int	move_character(int keycode, t_vars *vars)  MOVE ON THE MAP
// {
//     double radians;

//     radians = angle_radians(STEP_ANGLE);
// 	if (keycode == D) //move right
// 	{
//         vars->posx = vars->posx + STEP;
// 		return (1);
// 	}
// 	else if (keycode == A) //move left
// 	{
//         vars->posx = vars->posx - STEP;
// 		return (1);
// 	}
// 	else if (keycode == S) //move down
// 	{
//         vars->posy = vars->posy - STEP;
// 		return (1);
// 	}
// 	else if (keycode == W) //move top
// 	{
//         vars->posy = vars->posy + STEP;
// 		return (1);
// 	}
//     else if (keycode == LEFT) //move top
// 	{
//         rotate_vector(vars, -radians);
// 		return (1);
// 	}
//     else if (keycode == RIGHT) //move top
// 	{
//         rotate_vector(vars, radians);
// 		return (1);
// 	}
// 	return (0);
// }

int box_collision(t_vars *vars, double x, double y)
{
    (void)vars;
    (void)x;
    (void)y;
    return (0);
    // int i;
    // int j;

    // i = 0;
    // j = 0;
    // while (i < 9)
    // {
    //     j = 0;
    //     while (j < 9)
    //     {
    //         if (vars->map[i][j] == '1')
    //         {
    //             if (x <= (double)i + GRID_SIZE / 2.0 && x >= (double)i - GRID_SIZE / 2.0 && y <= (double)j + GRID_SIZE / 2.0 && y >= (double)j - GRID_SIZE / 2.0)
    //                 return (1);
    //         }
    //         j++;
    //     }
    //     i++;
    // }
    // return (0);
}

int	move_character(int keycode, t_vars *vars)
{
    double radians;

    double magnitude;
    double dirx;
    double diry;

    magnitude = sqrt(vars->dirx * vars->dirx + vars->diry * vars->diry);
    dirx = vars->dirx / magnitude;
    diry = vars->diry / magnitude;

    radians = angle_radians(STEP_ANGLE);
	if (keycode == A) //move left
	{
        if (box_collision(vars, vars->posx + STEP * diry, vars->posy - STEP * dirx))
            return (0);
        vars->posx = vars->posx + STEP * diry;
        vars->posy = vars->posy - STEP * dirx;
		return (1);
	}
	else if (keycode == D) //move right
	{
        if (box_collision(vars, vars->posx - STEP * diry, vars->posy + STEP * dirx))
            return (0);
        vars->posx = vars->posx - STEP * diry;
        vars->posy = vars->posy + STEP * dirx;
		return (1);
	}
	else if (keycode == W) //move forward
	{
        if (box_collision(vars, vars->posx - STEP * dirx, vars->posy - STEP * diry))
            return (0);
        vars->posx = vars->posx - STEP * dirx;
        vars->posy = vars->posy - STEP * diry;
		return (1);
	}
	else if (keycode == S) //move back
	{
        if (box_collision(vars, vars->posx + STEP * dirx, vars->posy + STEP * diry))
            return (0);
        vars->posx = vars->posx + STEP * dirx;
        vars->posy = vars->posy + STEP * diry;
		return (1);
	}
    else if (keycode == LEFT) //move top
	{
        rotate_vector(vars, -radians);
		return (1);
	}
    else if (keycode == RIGHT) //move top
	{
        rotate_vector(vars, radians);
		return (1);
	}
	return (0);
}

void draw_ray(t_vars *vars, double fov)
{
    t_vector ray[(int)SAMPLE + 1];
    double sample_angle = fov / SAMPLE;
    double sample_radians = angle_radians(sample_angle);
    double radians = angle_radians(-fov / 2); // 从视野左侧开始的角度

    for (int i = 0; i < (int)SAMPLE + 1; i++)////////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_direction_vector(&ray[i]);
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x, vars->posy * BOX_SIZE + ray[i].y, WHITE);
        radians += sample_radians; // 每次累加固定的增量角度
    }
}


////////////////////////////////////////

# define MIN_ERR 0.0000000001

int double_equal(double a, double b)
{
    if (ft_abs(b - a) < MIN_ERR)
        return (1);
    return (0);
}

int on_box(double x_center, double y_center, double x, double y)
{
    double top_y = y_center + GRID_SIZE / 2.0;
    double bottom_y = y_center - GRID_SIZE / 2.0;
    double left_x = x_center - GRID_SIZE / 2.0;
    double right_x = x_center + GRID_SIZE / 2.0;

    if (double_equal(x, left_x) && y >= bottom_y + MIN_ERR && y <= top_y - MIN_ERR)
            return (WEST);
    else if (double_equal(x, right_x) && y >= bottom_y + MIN_ERR && y <= top_y - MIN_ERR)
            return (EAST);
    else if (double_equal(y, top_y) && x >= left_x + MIN_ERR && x <= right_x - MIN_ERR)
            return (NORTH);
    else if (double_equal(y, bottom_y) && x >= left_x + MIN_ERR && x <= right_x - MIN_ERR)
            return (SOUTH);
    return (NOT_ONBOX);
}

double len_2pt(double x1, double y1, double x2, double y2)
{
    double  sqr;

    sqr = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (sqr);
}

double dist_towall(t_vars *vars, double x, double y, int *color)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if (vars->map[i][j] == '1')
                if (on_box((double)j + GRID_SIZE / 2.0, (double)i + GRID_SIZE / 2.0, x, y) != NOT_ONBOX)
                {
                    *color = on_box((double)j + GRID_SIZE / 2.0, (double)i + GRID_SIZE / 2.0, x, y);
                    return (len_2pt(vars->posx, vars->posy, x, y));
                }
            j++;
        }
        i++;
    }
    return (-1);
}

#define S_SIZE 50

double check_close_wall(t_vars *vars, t_vector *vector, int *color, int i)
{
    double x = vars->posx;  // 出发点 x 坐标
    double y = vars->posy;  // 出发点 y 坐标
    double dx = vector->x;  // 已归一化的方向向量 x 分量
    double dy = vector->y;  // 已归一化的方向向量 y 分量

    int step_x = (dx > 0) ? 1 : -1;  // x 方向步长（+1 或 -1）
    int step_y = (dy > 0) ? 1 : -1;  // y 方向步长（+1 或 -1）

    double t_max_x = (step_x > 0) ? ceil(x) - x : x - floor(x);  // 到达下一个 x 网格线的时间
    double t_max_y = (step_y > 0) ? ceil(y) - y : y - floor(y);  // 到达下一个 y 网格线的时间
    t_max_x /= ft_abs(dx);  // 归一化时间
    t_max_y /= ft_abs(dy);  // 归一化时间

    double t_delta_x = 1.0 / ft_abs(dx);  // 每次跨越一个 x 网格的时间增量
    double t_delta_y = 1.0 / ft_abs(dy);  // 每次跨越一个 y 网格的时间增量

    // 初始网格坐标
    int map_x = (int)floor(x);
    int map_y = (int)floor(y);

    double intersect_x = x;
    double intersect_y = y;
    double distance_towall;

    // 运行 DDA 算法
    while (1) {
        if (t_max_x < t_max_y) {
            map_x += step_x;  // 前进到下一个 x 网格线
            intersect_x = x + t_max_x * dx;
            intersect_y = y + t_max_x * dy;
            t_max_x += t_delta_x;  // 更新 t_max_x
        } else {
            map_y += step_y;  // 前进到下一个 y 网格线
            intersect_x = x + t_max_y * dx;
            intersect_y = y + t_max_y * dy;
            t_max_y += t_delta_y;  // 更新 t_max_y
        }
        // 可根据需要在此处添加条件判断（例如检测碰撞或其他逻辑）
        distance_towall = dist_towall(vars, intersect_x, intersect_y, &color[i]);
        if (distance_towall >= 0)
        {
            return (distance_towall);
        }
        if (len_2pt(x, y, intersect_x, intersect_y) > 5000.0) 
        {
            return(5000.0);
        }
    }
    return 0;
}


# define POSITION_X 500
# define DISPLAY_W 500.0
# define DISPLAY_H 300.0
# define POSITION_Y 300
# define NUMM 100

void draw_line_up_down(t_vars *vars, int i, double distance, int *color)
{
    int color_final = WHITE;
    double wall_height = DISPLAY_H / distance;

    if (color[i] == WEST)
        color_final = RED;
    else if (color[i] == EAST)
        color_final = BLUE;
    else if (color[i] == NORTH)
        color_final = GREEN;
    else if (color[i] == SOUTH)
        color_final = YELLOW;
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y + wall_height / 2, color_final);
    draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y - wall_height / 2, color_final);
}


double vector_projlen(double x1, double y1, double x2, double y2)
{
    double len;

    len = (x1 * x2 + y1 * y2) / sqrt(x2 * x2 + y2 * y2) / 100; 
    return (len);
}

void check_visibility(t_vars *vars, double fov)
{
    t_vector ray[(int)SAMPLE + 1]; 
    int *ray_color = malloc(sizeof(int) * ((int)SAMPLE + 1));
    if (!ray_color)
        return;

    double sample_angle = fov / SAMPLE;
    double sample_radians = angle_radians(sample_angle);
    double radians = angle_radians(-fov / 2.0); // 从视野左侧开始的角度

    int i = 0;
    double distance = 0;
    while (i < (int)SAMPLE + 1)///////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_vector(&ray[i], 1);
        distance = check_close_wall(vars, &ray[i], ray_color, i);
        ray[i].x *= distance;
        ray[i].y *= distance;
        distance = distance * cos(angle_radians(i * sample_angle - fov / 2.0));
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x * BOX_SIZE, vars->posy * BOX_SIZE + ray[i].y * BOX_SIZE, WHITE);
        draw_line_up_down(vars, i, distance, ray_color);
        radians += sample_radians;
        i++;
    }
}

void draw_screen(t_vars *vars, double fov)
{
    t_vector ray[2];

    double radians = angle_radians(-fov / 2); // 从视野左侧开始的角度
    for (int i = 0; i < 2; i++)/////////////////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_screen_vector(&ray[i]);
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x, vars->posy * BOX_SIZE + ray[i].y, BLUE);
        radians += angle_radians(FOV); // 每次累加固定的增量角度
    }
    draw_line(vars, vars->posx * BOX_SIZE + ray[0].x, vars->posy * BOX_SIZE + ray[0].y, vars->posx * BOX_SIZE + ray[1].x, vars->posy * BOX_SIZE + ray[1].y, BLUE);
}

void draw_map(t_vars *vars, double x, double y, double size)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < 9)
    {
        j = 0;
        while (j < 9)
        {
            if (vars->map[j][i] == '1')
                draw_box(vars, x + i * size, y + j * size, size);
            j++;
        }
        i++;
    }
}

void    render_game(t_vars *vars)
{
    check_visibility(vars, FOV);
    draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + vars->dirx, vars->posy * BOX_SIZE + vars->diry, RED);
    draw_screen(vars, FOV);
    draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
}

// void draw_line_in_buf(t_vars *vars, int idx, double distance, int *color, int *buf_data)
// {
//     int color_final = WHITE;
//     //double wall_height = DISPLAY_H / distance;

//     (void)vars;
//     (void)distance;
//     if (color[idx] == WEST)
//         color_final = RED;
//     else if (color[idx] == EAST)
//         color_final = BLUE;
//     else if (color[idx] == NORTH)
//         color_final = GREEN;
//     else if (color[idx] == SOUTH)
//         color_final = YELLOW;
//     // draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y + wall_height / 2, color_final);
//     // draw_line(vars, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y, (POSITION_X + i * (DISPLAY_W / SAMPLE)), POSITION_Y - wall_height / 2, color_final);
//     int i = 0;
//     int j = 0;
//     while (j <SCREEN_HEIGHT)
//     {
//         i = 0;
//         while (i < SCREEN_WIDTH)
//         {
//             if (i == 100)   
//                 buf_data[j * SCREEN_WIDTH + i] = color_final;
//             i++;
//         }
//         j++;
//     }
// }


// void game_buf(t_vars *vars, double fov, int *buf_data)
// {
//     t_vector ray[(int)SAMPLE + 1]; 
//     int *ray_color = malloc(sizeof(int) * ((int)SAMPLE + 1));
//     if (!ray_color)
//         return;

//     double sample_angle = fov / SAMPLE;
//     double sample_radians = angle_radians(sample_angle);
//     double radians = angle_radians(-fov / 2.0); // 从视野左侧开始的角度
//     int i = 0;
//     double distance = 0;
//     while (i < (int)SAMPLE + 1)///////////////////////////////
//     {
//         ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
//         ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
//         normalize_vector(&ray[i], 1);
//         distance = check_close_wall(vars, &ray[i], ray_color, i);
//         ray[i].x *= distance;
//         ray[i].y *= distance;
//         distance = distance * cos(angle_radians(i * sample_angle - fov / 2.0));
//         draw_line_in_buf(vars, i, distance, ray_color, buf_data);
//         radians += sample_radians;
//         i++;
//     }
// }

// void    render_game_buf(t_vars *vars)
// {
//     //void *buf_img;
//     int  *buf_data;
//     int  bpp, size_line, endian;

//     //buf_img = mlx_new_image(vars->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
//     buf_data = (int *)mlx_get_data_addr(vars->buf_img, &bpp, &size_line, &endian);
//     ft_memset(vars->buf_img, 0, sizeof(int) * SCREEN_HEIGHT * size_line);

//     game_buf(vars, FOV, buf_data);
//     mlx_put_image_to_window(vars->mlx, vars->win, vars->buf_img, 0, 0);
// }

int	key_control(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		//destroy_vars(vars);
		exit(0);
	}
	move_character(keycode, vars);
    mlx_clear_window(vars->mlx, vars->win);
    render_game(vars);
    //render_game_buf(vars);
	return (0);
}

int main(void)
{
    t_vars vars;

    char map[9][9] = {
    "11111111",
    "1N100001",
    "10100001",
    "10000001",
    "10011111",
    "10010001",
    "10010101",
    "10000001",
    "11111111",
    };

    (&vars)->map = map;
    (&vars)->posx = 1.5;
    (&vars)->posy = 1.5;
    (&vars)->dirx = SCALE;
    (&vars)->diry = 0;

    (&vars)->mlx = mlx_init();
    (&vars)->buf_img = mlx_new_image((&vars)->mlx, SCREEN_HEIGHT, SCREEN_WIDTH);
    (&vars)->win = mlx_new_window((&vars)->mlx, SCREEN_HEIGHT, SCREEN_WIDTH, "cub3d");
    draw_line(&vars, vars.posx * BOX_SIZE, vars.posy * BOX_SIZE, vars.posx * BOX_SIZE+vars.dirx, vars.posy * BOX_SIZE+vars.diry, RED);
    mlx_hook(vars.win, 2, (1L << 0), key_control, &vars);
    mlx_loop(vars.mlx);
    return (0);
}