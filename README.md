# cub3D

A 3D graphical game project made at 42 school, using raycasting to render a simple first-person perspective view inspired by Wolfenstein 3D.
Developed in C using the MinilibX graphics library.

# Description

cub3D is a small 3D game engine built from scratch. It parses a .cub map file, loads textures, and renders a 3D environment using raycasting. The player can move around, rotate their view, and interact with the world.

This project is part of the 42 cursus and serves as an introduction to basic graphical programming and game rendering techniques.

# Mandatory Features

 Map parsing from .cub file (with error checking)

 Raycasting rendering engine

 Movement: forward, backward, strafe, rotation

 Wall textures (4 directions)

 Floor and ceiling color/textures

 Mini-map (zoomable)

 Collision detection

 Mouse control

# Bonus Features
 Smooth mini-map with zoom in/out support

 Simulated shadow effect for added depth (pseudo-lighting)

 HUD with a health bar

 Crosshair in the center

 FPS counter (F)

 Mouse look support (optional)

# Key Concepts
Raycasting (DDA algorithm)

Texture mapping

Event handling (keyboard/mouse)

MinilibX usage (X11 on Linux or macOS)

2D to 3D projection logic

Modular C code structure and memory management

# Build Instructions
bash

# Compile
make        # for mandatory part
make bonus  # for bonus features

# Run
./cub3D maps/your_map.cub
# Map Format
A .cub map file includes:

Texture paths for walls

Floor and ceiling colors/textures

2D map (with 1 for walls, 0 for empty space, N/E/S/W for player start)

Example:

NO ./textures/wall_north.xpm

SO ./textures/wall_south.xpm

WE ./textures/wall_west.xpm

EA ./textures/wall_east.xpm

F 220,100,0

C 225,30,0


111111
100001
1000N1
111111

# Controls

Key	Action
W/A/S/D	Move forward/left/back/right
←/→	Rotate view left/right
M	Toggle mini-map
+/-	Zoom mini-map
Esc	Exit game
Mouse	Look around (if enabled)
9 0 shadow

# Notes
The code follows the 42 Norm.

No external libraries were used beyond MinilibX and syscall.

Developed and tested under Linux with MinilibX.

Only for educational use.
