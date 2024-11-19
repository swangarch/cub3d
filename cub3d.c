# include "libft.h"
# include "mlx.h"
# include <math.h>
# include <stdio.h>

# define SCREEN_HEIGHT 1024
# define SCREEN_WIDTH 768

# define SCALE 500
# define SCALE_SCREEN 150
# define STEP 0.1
# define STEP_ANGLE 2
# define SAMPLE 60
# define FOV 60.0
# define BOX_SIZE 50
# define GRID_SIZE 0.5

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

double angle_radians(int angle)
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

int ft_abs(int num)
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

int	move_character(int keycode, t_vars *vars)
{
    double radians;

    radians = angle_radians(STEP_ANGLE);
	if (keycode == D) //move right
	{
        vars->posx = vars->posx + STEP;
		return (1);
	}
	else if (keycode == A) //move left
	{
        vars->posx = vars->posx - STEP;
		return (1);
	}
	else if (keycode == S) //move down
	{
        vars->posy = vars->posy - STEP;
		return (1);
	}
	else if (keycode == W) //move top
	{
        vars->posy = vars->posy + STEP;
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
    t_vector ray[SAMPLE + 1];
    double sample_angle = fov / SAMPLE;
    double sample_radians = angle_radians(sample_angle);
    double radians = angle_radians(-fov / 2); // 从视野左侧开始的角度

    for (int i = 0; i < SAMPLE + 1; i++)////////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_direction_vector(&ray[i]);
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x, vars->posy * BOX_SIZE + ray[i].y, WHITE);
        radians += sample_radians; // 每次累加固定的增量角度
    }
}


////////////////////////////////////////

# define MIN_ERR 0.01

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

    if (double_equal(x, left_x) && y >= bottom_y && y <= top_y)
            return (WEST);
    else if (double_equal(x, right_x) && y >= bottom_y && y <= top_y)
            return (EAST);
    else if (double_equal(y, top_y) && x >= left_x && x <= right_x)
            return (NORTH);
    else if (double_equal(y, bottom_y) && x >= left_x && x <= right_x)
            return (SOUTH);
    return (NOT_ONBOX);
}

double len_2pt(double x1, double y1, double x2, double y2)
{
    double  sqr;

    sqr = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    return (sqr);
}

double dist_towall(t_vars *vars, double x, double y)
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
                if (on_box(i + GRID_SIZE / 2, j + GRID_SIZE / 2, x, y) != NOT_ONBOX)
                    return (len_2pt(vars->posx, vars->posy, x, y));
            j++;
        }
        i++;
    }
    return (-1);
}

#define S_SIZE 50

double check_close_wall(t_vars *vars, t_vector *vector)
{
    double x = vars->posx;
    double y = vars->posy;
    double dx = vector->x; // 已归一化的方向向量
    double dy = vector->y;

    // 初始格子坐标
    int grid_x = (int)x;
    int grid_y = (int)y;

    // 增量方向
    int step_x = (dx > 0) ? 1 : -1;
    int step_y = (dy > 0) ? 1 : -1;

    // 初始 t 值
    double t_max_x = (step_x > 0 ? (grid_x + 1.0 - x) : (x - grid_x));
    double t_max_y = (step_y > 0 ? (grid_y + 1.0 - y) : (y - grid_y));

    // t 的增量
    double t_delta_x = 1.0 / ft_abs(dx);
    double t_delta_y = 1.0 / ft_abs(dy);

    // 遍历格子
    while (1)
    {
        // 输出当前相交点的坐标
        double intersection_x, intersection_y;

        if (t_max_x < t_max_y)
        {
            intersection_x = (step_x > 0) ? (grid_x + 1.0) : grid_x;
            intersection_y = y + t_max_x * dy;
            printf("Intersection: (%f, %f)\n", intersection_x, intersection_y);
            mlx_pixel_put((vars)->mlx, (vars)->win, intersection_x * S_SIZE, intersection_y * S_SIZE, RED);

            // 更新 t_max_x 和 grid_x
            t_max_x += t_delta_x;
            grid_x += step_x;
        }
        else
        {
            intersection_x = x + t_max_y * dx;
            intersection_y = (step_y > 0) ? (grid_y + 1.0) : grid_y;
            printf("Intersection: (%f, %f)\n", intersection_x, intersection_y);
            mlx_pixel_put((vars)->mlx, (vars)->win, intersection_x * S_SIZE, intersection_y * S_SIZE, RED);

            // 更新 t_max_y 和 grid_y
            t_max_y += t_delta_y;
            grid_y += step_y;
        }

        // 停止条件：根据需要修改
        if (dist_towall(vars, intersection_x, intersection_y) >= 0)
            return (write(1,"case\n", 5), dist_towall(vars, intersection_x, intersection_y));
        if (len_2pt(x, y, intersection_x, intersection_y) > 1000)
            return (1000);
    }
    return 0;
}

void check_visibility(t_vars *vars, double fov)
{
    t_vector ray[SAMPLE + 1];
    double sample_angle = fov / SAMPLE;
    double sample_radians = angle_radians(sample_angle);
    double radians = angle_radians(-fov / 2); // 从视野左侧开始的角度

    int i = 0;
    double distance = 0;
    while (i < SAMPLE + 1)///////////////////////////////
    {
        ray[i].x = vars->dirx * cos(radians) - vars->diry * sin(radians);
        ray[i].y = vars->dirx * sin(radians) + vars->diry * cos(radians);
        normalize_vector(&ray[i], 1);
        distance = check_close_wall(vars, &ray[i]);
        ray[i].x *= distance;
        ray[i].y *= distance;
        //normalize_vector(&ray[i], 1000);
        draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + ray[i].x * BOX_SIZE, vars->posy * BOX_SIZE + ray[i].y * BOX_SIZE, WHITE);
        
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

void    render_plan(t_vars *vars)
{
    //draw_ray(vars, FOV);
    check_visibility(vars, FOV);
    draw_line(vars, vars->posx * BOX_SIZE, vars->posy * BOX_SIZE, vars->posx * BOX_SIZE + vars->dirx, vars->posy * BOX_SIZE + vars->diry, RED);
    draw_screen(vars, FOV);
    draw_map(vars, BOX_SIZE / 2, BOX_SIZE / 2, BOX_SIZE);
}

int	key_control(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		//destroy_vars(vars);
		exit(0);
	}
	move_character(keycode, vars);
    mlx_clear_window(vars->mlx, vars->win);
    render_plan(vars);
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
    "10010001",
    "10000001",
    "11111111",
    };

    (&vars)->map = map;
    (&vars)->posx = 1.5;
    (&vars)->posy = 1.5;
    (&vars)->dirx = SCALE;
    (&vars)->diry = 0;

    (&vars)->mlx = mlx_init();
    (&vars)->win = mlx_new_window((&vars)->mlx, SCREEN_HEIGHT, SCREEN_WIDTH, "cub3d");
    draw_line(&vars, vars.posx * BOX_SIZE, vars.posy * BOX_SIZE, vars.posx * BOX_SIZE+vars.dirx, vars.posy * BOX_SIZE+vars.diry, RED);
    mlx_hook(vars.win, 2, (1L << 0), key_control, &vars);
    mlx_loop(vars.mlx);
    return (0);
}