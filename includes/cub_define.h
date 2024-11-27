#ifndef CUB_DEFINE_H
# define CUB_DEFINE_H

# define MES_ERR "Error\n"
# define MES_NO_MAP_ERR "No map specified!\n"
# define MES_TOO_MANY_ARG_ERR "Too many arguments for map!\n"
# define MES_WRONG_NAME_ERR "Wrong map name! Ended by .cub!\n"
# define MES_MLX_INIT_ERR "Mlx init failed!\n"
# define MES_NEW_WIN_ERR "Open new window failed!\n"
# define MES_INVALD_MAP_ERR "Invalid map!\n"
# define MES_OPEN_ERR "Cannot open the map!\n"

# define LEN_TYPE 7
# define LEN_TEX 5

# define T_NORTH 0
# define T_SOUTH 1
# define T_WEST 2
# define T_EAST 3
# define T_FLOOR 4
# define T_CEILING 5
# define T_MAP 6

/*********************************************************/

# define FPS 60

/*SCREEN*/
# define SCREEN_HEIGHT 720
# define SCREEN_WIDTH 1280

/*MAP*/
// # define MAP_POSX 100
// # define MAP_POSY 100
# define BOX_SIZE 10.0

/*SAMPLE PARAM*/
# define SCALE 1
# define SCALE_SCREEN 150.0
# define STEP 0.05
# define STEP_ANGLE 1
# define STEP_ANGLE_MOUSE 0.007
# define STEP_HEIGHT_RATIO 0.05
# define SAMPLE 1280
//# define SAMPLE 4
# define FOV 60.0
# define GRID_SIZE 1

# define MAX_VIEW_DISTANCE 1000.0
# define MIN_WALL_DISTANCE 0.1

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
# define W 119
# define S 115
# define LEFT 65361
# define LEFT_INT 128
# define RIGHT 65363
# define RIGHT_INT 129
# define UP 65362
# define UP_INT 130
# define DOWN 65364
# define DOWN_INT 131

/*ORIENTATION*/
# define NORTH 1
# define EAST 2
# define SOUTH 3
# define WEST 4
# define NOT_ONBOX 0

/*TEXTURE*/
# define TEXTURE_SIZE 256

/*DOUBLE ERROR*/
# define MIN_ERR 0.000000000001
# define MIN_ERR2 0.0

/*RENDER ON THE SCREEN*/
# define POSITION_X 0
# define DISPLAY_W 1280
# define DISPLAY_H 768
# define POSITION_Y 384

/*TIME INTERVAL CONTROL*/
# define TIME_ITVAL_MOUSE 10000

# define FADE 1
# define SHADOW 1

#endif
