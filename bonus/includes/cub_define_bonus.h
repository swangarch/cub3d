/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_define_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yfan <yfan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 16:52:48 by yfan              #+#    #+#             */
/*   Updated: 2024/12/09 16:52:49 by yfan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_DEFINE_BONUS_H
# define CUB_DEFINE_BONUS_H

# define MES_ERR "Error\n"
# define MES_NO_MAP_ERR "No map specified!\n"
# define MES_TOO_MANY_ARG_ERR "Too many arguments for map!\n"
# define MES_WRONG_NAME_ERR "Wrong map name! Ended by .cub!\n"
# define MES_MLX_INIT_ERR "Mlx init failed!\n"
# define MES_NEW_WIN_ERR "Open new window failed!\n"
# define MES_INVALD_MAP_ERR "Invalid map!\n"
# define MES_OPEN_ERR "Cannot open the map!\n"

# define LEN_TYPE 13
# define LEN_TEX 11

# define T_NORTH 0
# define T_SOUTH 1
# define T_WEST 2
# define T_EAST 3
# define T_OBJ 4
# define T_OBJ_SP 5
# define T_SOUTH_SP 6
# define T_WEST_SP 7
# define T_FLOOR_SP 8
# define T_CEILING_SP 9
# define T_FLOOR 10
# define T_CEILING 11
# define T_MAP 12

# define FPS 48

# define SCREEN_HEIGHT 450
# define SCREEN_WIDTH 800

# define MAP_SIZE 8.0
# define SHADSIZ 0.25

/*SAMPLE PARAM*/
# define SCALE 1
# define SCALE_SCREEN 150.0
# define STEP 0.05
# define CK_STEP 3.0
# define STEP_ANGLE 1
# define STEP_ANGLE_MOUSE 0.007
# define SAMPLE SCREEN_WIDTH
# define FOV 60.0
# define GRID_SIZE 1
# define HEIGHT_RATIO 1.5

# define MAX_VIEW_DISTANCE 500.0
# define MIN_WALL_DISTANCE 0.1

/*COLORS*/
# define GREEN -16711936
# define RED -65536
# define BLUE -16776961
# define YELLOW -256
# define WHITE -1
# define CYAN -16711681
# define MAGENTA -65281
# define GREY_L 15000804
# define GREY_M 12239561

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
# define M 109
# define E 101
# define F 102
# define O 111
# define P 112
# define NUM_9 57
# define NUM_0 48

# define PRESSED 1
# define RELEASED 0

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

# define S_SIZE 50
# define VERY_LARGE_VALUE 1e30

/*RENDER ON THE SCREEN*/
# define POSITION_X 0
# define DISPLAY_W SCREEN_WIDTH
# define DISPLAY_H SCREEN_HEIGHT

/*TIME INTERVAL CONTROL*/
# define TIME_ITVAL_MOUSE 10000
# define SKY 1

/*UI*/
# define HP_W 100
# define HP_H 10

#endif
