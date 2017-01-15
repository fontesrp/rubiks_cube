//
//  rubik_cube.h
//  rubiks_cube
//
//  Created by Rodrigo Fontes on 12/1/17.
//

#ifndef rubik_cube_h
#define rubik_cube_h

#include <stdio.h>

#define FACE_ROWS 3
#define FACE_COLS 3
#define FACE_SQUARES FACE_ROWS * FACE_COLS
#define CUBE_FACES 6
#define CUBE_SQUARES CUBE_FACES * FACE_SQUARES
#define MAX_MOV_LEN 3

enum squareColor {
    RED,
    WHITE,
    BLUE,
    ORANGE,
    GREEN,
    YELLOW
};

enum faceNames {
    F, // Front
    U, // Up
    R, // Right
    B, // Back
    L, // Left
    D  // Down
};

struct cubeFace {
    unsigned char squares[FACE_ROWS][FACE_COLS];
};

struct rubikCube {
    struct cubeFace faces[CUBE_FACES];
};

char getFaceName(unsigned char face);
unsigned char int2color(int color);
void setRowColors(struct rubikCube * cube, unsigned char face, unsigned char row, unsigned char * rowColors);
void getRelativeFaces(unsigned char face, unsigned char * upFace, unsigned char * rightFace, unsigned char * downFace, unsigned char * leftFace, unsigned char * backFace);
void faceRotation(struct rubikCube * cube, char faceName, char directionModifier, char lengthModifier);
void printCube(struct rubikCube * cube);
void initilizeCube(struct rubikCube * cube);

#endif // rubik_cube_h
