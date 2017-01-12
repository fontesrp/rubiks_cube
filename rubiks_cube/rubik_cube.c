//
//  rubik_cube.c
//  rubiks_cube
//
//  Created by Rodrigo Fontes on 12/1/17.
//

#include "rubik_cube.h"

char getFaceName(unsigned char face) {
    switch (face) {
    case F:
        return 'F';
    case U:
        return 'U';
    case R:
        return 'R';
    case B:
        return 'B';
    case L:
        return 'L';
    case D:
        return 'D';
    default:
        return '\0';
    }
}

unsigned char int2color(int color) {
    switch (color) {
    case 'R':
    case 'r':
        return RED;
    case 'W':
    case 'w':
        return WHITE;
    case 'B':
    case 'b':
        return BLUE;
    case 'O':
    case 'o':
        return ORANGE;
    case 'G':
    case 'g':
        return GREEN;
    case 'Y':
    case 'y':
        return YELLOW;
    case '\n':
    case '\0':
    case EOF:
        return 127u;
    default:
        return 255u;
    }
}

static unsigned char getSquare(struct rubikCube * cube, unsigned char face, unsigned char row, unsigned char col) {
    return cube->faces[face].squares[row][col];
}

static void setSquare(struct rubikCube * cube, unsigned char face, unsigned char row, unsigned char col, unsigned char value) {
    cube->faces[face].squares[row][col] = value;
}

void setRowColors(struct rubikCube * cube, unsigned char face, unsigned char row, unsigned char * rowColors) {
    unsigned char col;
    for (col = 0; col < FACE_COLS; col++) {
        setSquare(cube, face, row, col, rowColors[col]);
    }
}

static void copySquare(struct rubikCube * cube, unsigned char rxFace, unsigned char rxRow, unsigned char rxCol, unsigned char txFace, unsigned char txRow, unsigned char txCol) {
    setSquare(cube, rxFace, rxRow, rxCol, getSquare(cube, txFace, txRow, txCol));
}

void getRelativeFaces(unsigned char face, unsigned char * upFace, unsigned char * rightFace, unsigned char * downFace, unsigned char * leftFace, unsigned char * backFace) {
    switch (face) {
    case F:
        *upFace = U;
        *rightFace = R;
        *downFace = D;
        *leftFace = L;
        *backFace = B;
        break;
    case U:
        *upFace = B;
        *rightFace = R;
        *downFace = F;
        *leftFace = L;
        *backFace = D;
        break;
    case R:
        *upFace = U;
        *rightFace = B;
        *downFace = D;
        *leftFace = F;
        *backFace = L;
        break;
    case B:
        *upFace = U;
        *rightFace = L;
        *downFace = D;
        *leftFace = R;
        *backFace = F;
        break;
    case L:
        *upFace = U;
        *rightFace = F;
        *downFace = D;
        *leftFace = B;
        *backFace = R;
        break;
    case D:
        *upFace = F;
        *rightFace = R;
        *downFace = B;
        *leftFace = L;
        *backFace = U;
        break;
    }
}

static void rotateFaceClockwise(struct rubikCube * cube, unsigned char face) {

    unsigned char tmp;

    // Rotate main face clockwise
    tmp = getSquare(cube, face, 0, 2);
    copySquare(cube, face, 0, 2, face, 0, 0); // (0, 2) <- (0, 0)
    copySquare(cube, face, 0, 0, face, 2, 0); // (0, 0) <- (2, 0)
    copySquare(cube, face, 2, 0, face, 2, 2); // (2, 0) <- (2, 2)
    setSquare(cube, face, 2, 2, tmp);         // (2, 2) <- (0, 2)
    tmp = getSquare(cube, face, 1, 2);
    copySquare(cube, face, 1, 2, face, 0, 1); // (1, 2) <- (0, 1)
    copySquare(cube, face, 0, 1, face, 1, 0); // (0, 1) <- (1, 0)
    copySquare(cube, face, 1, 0, face, 2, 1); // (1, 0) <- (2, 1)
    setSquare(cube, face, 2, 1, tmp);         // (2, 1) <- (1, 2)

    // Rotate adjacent squares
    switch (face) {
    case F:
        tmp = getSquare(cube, U, 2, 0);
        copySquare(cube, U, 2, 0, L, 2, 2); // U(2, 0) <- L(2, 2)
        copySquare(cube, L, 2, 2, D, 0, 2); // L(2, 2) <- D(0, 2)
        copySquare(cube, D, 0, 2, R, 0, 0); // D(0, 2) <- R(0, 0)
        setSquare(cube, R, 0, 0, tmp);      // R(0, 0) <- U(2, 0)
        tmp = getSquare(cube, U, 2, 1);
        copySquare(cube, U, 2, 1, L, 1, 2); // U(2, 1) <- L(1, 2)
        copySquare(cube, L, 1, 2, D, 0, 1); // L(1, 2) <- D(0, 1)
        copySquare(cube, D, 0, 1, R, 1, 0); // D(0, 1) <- R(1, 0)
        setSquare(cube, R, 1, 0, tmp);      // R(1, 0) <- U(2, 1)
        tmp = getSquare(cube, U, 2, 2);
        copySquare(cube, U, 2, 2, L, 0, 2); // U(2, 2) <- L(0, 2)
        copySquare(cube, L, 0, 2, D, 0, 0); // L(0, 2) <- D(0, 0)
        copySquare(cube, D, 0, 0, R, 2, 0); // D(0, 0) <- R(2, 0)
        setSquare(cube, R, 2, 0, tmp);      // R(2, 0) <- U(2, 2)
        break;
    case U:
        tmp = getSquare(cube, F, 0, 0);
        copySquare(cube, F, 0, 0, R, 0, 0); // F(0, 0) <- R(0, 0)
        copySquare(cube, R, 0, 0, B, 0, 0); // R(0, 0) <- B(0, 0)
        copySquare(cube, B, 0, 0, L, 0, 0); // B(0, 0) <- L(0, 0)
        setSquare(cube, L, 0, 0, tmp);      // L(0, 0) <- F(0, 0)
        tmp = getSquare(cube, F, 0, 1);
        copySquare(cube, F, 0, 1, R, 0, 1); // F(0, 1) <- R(0, 1)
        copySquare(cube, R, 0, 1, B, 0, 1); // R(0, 1) <- B(0, 1)
        copySquare(cube, B, 0, 1, L, 0, 1); // B(0, 1) <- L(0, 1)
        setSquare(cube, L, 0, 1, tmp);      // L(0, 1) <- F(0, 1)
        tmp = getSquare(cube, F, 0, 2);
        copySquare(cube, F, 0, 2, R, 0, 2); // F(0, 2) <- R(0, 2)
        copySquare(cube, R, 0, 2, B, 0, 2); // R(0, 2) <- B(0, 2)
        copySquare(cube, B, 0, 2, L, 0, 2); // B(0, 2) <- L(0, 2)
        setSquare(cube, L, 0, 2, tmp);      // L(0, 2) <- F(0, 2)
        break;
    case R:
        tmp = getSquare(cube, F, 0, 2);
        copySquare(cube, F, 0, 2, D, 0, 2); // F(0, 2) <- D(0, 2)
        copySquare(cube, D, 0, 2, B, 2, 0); // D(0, 2) <- B(2, 0)
        copySquare(cube, B, 2, 0, U, 0, 2); // B(2, 0) <- U(0, 2)
        setSquare(cube, U, 0, 2, tmp);      // U(0, 2) <- F(0, 2)
        tmp = getSquare(cube, F, 1, 2);
        copySquare(cube, F, 1, 2, D, 1, 2); // F(1, 2) <- D(1, 2)
        copySquare(cube, D, 1, 2, B, 1, 0); // D(1, 2) <- B(1, 0)
        copySquare(cube, B, 1, 0, U, 1, 2); // B(1, 0) <- U(1, 2)
        setSquare(cube, U, 1, 2, tmp);      // U(1, 2) <- F(1, 2)
        tmp = getSquare(cube, F, 2, 2);
        copySquare(cube, F, 2, 2, D, 2, 2); // F(2, 2) <- D(2, 2)
        copySquare(cube, D, 2, 2, B, 0, 0); // D(2, 2) <- B(0, 0)
        copySquare(cube, B, 0, 0, U, 2, 2); // B(0, 0) <- U(2, 2)
        setSquare(cube, U, 2, 2, tmp);      // U(2, 2) <- F(2, 2)
        break;
    case B:
        tmp = getSquare(cube, U, 0, 0);
        copySquare(cube, U, 0, 0, R, 0, 2); // U(0, 0) <- R(0, 2)
        copySquare(cube, R, 0, 2, D, 2, 2); // R(0, 2) <- D(2, 2)
        copySquare(cube, D, 2, 2, L, 2, 0); // D(2, 2) <- L(2, 0)
        setSquare(cube, L, 2, 0, tmp);      // L(2, 0) <- U(0, 0)
        tmp = getSquare(cube, U, 0, 1);
        copySquare(cube, U, 0, 1, R, 1, 2); // U(0, 1) <- R(1, 2)
        copySquare(cube, R, 1, 2, D, 2, 1); // R(1, 2) <- D(2, 1)
        copySquare(cube, D, 2, 1, L, 1, 0); // D(2, 1) <- L(1, 0)
        setSquare(cube, L, 1, 0, tmp);      // L(1, 0) <- U(0, 1)
        tmp = getSquare(cube, U, 0, 2);
        copySquare(cube, U, 0, 2, R, 2, 2); // U(0, 2) <- R(2, 2)
        copySquare(cube, R, 2, 2, D, 2, 0); // R(2, 2) <- D(2, 0)
        copySquare(cube, D, 2, 0, L, 0, 0); // D(2, 0) <- L(0, 0)
        setSquare(cube, L, 0, 0, tmp);      // L(0, 0) <- U(0, 2)
        break;
    case L:
        tmp = getSquare(cube, F, 0, 0);
        copySquare(cube, F, 0, 0, U, 0, 0); // F(0, 0) <- U(0, 0)
        copySquare(cube, U, 0, 0, B, 2, 2); // U(0, 0) <- B(2, 2)
        copySquare(cube, B, 2, 2, D, 0, 0); // B(2, 2) <- D(0, 0)
        setSquare(cube, D, 0, 0, tmp);      // D(0, 0) <- F(0, 0)
        tmp = getSquare(cube, F, 1, 0);
        copySquare(cube, F, 1, 0, U, 1, 0); // F(1, 0) <- U(1, 0)
        copySquare(cube, U, 1, 0, B, 1, 2); // U(1, 0) <- B(1, 2)
        copySquare(cube, B, 1, 2, D, 1, 0); // B(1, 2) <- D(1, 0)
        setSquare(cube, D, 1, 0, tmp);      // D(1, 0) <- F(1, 0)
        tmp = getSquare(cube, F, 2, 0);
        copySquare(cube, F, 2, 0, U, 2, 0); // F(2, 0) <- U(2, 0)
        copySquare(cube, U, 2, 0, B, 0, 2); // U(2, 0) <- B(0, 2)
        copySquare(cube, B, 0, 2, D, 2, 0); // B(0, 2) <- D(2, 0)
        setSquare(cube, D, 2, 0, tmp);      // D(2, 0) <- F(2, 0)
        break;
    case D:
        tmp = getSquare(cube, F, 2, 0);
        copySquare(cube, F, 2, 0, L, 2, 0); // F(2, 0) <- L(2, 0)
        copySquare(cube, L, 2, 0, B, 2, 0); // L(2, 0) <- B(2, 0)
        copySquare(cube, B, 2, 0, R, 2, 0); // B(2, 0) <- R(2, 0)
        setSquare(cube, R, 2, 0, tmp);      // R(2, 0) <- F(2, 0)
        tmp = getSquare(cube, F, 2, 1);
        copySquare(cube, F, 2, 1, L, 2, 1); // F(2, 1) <- L(2, 1)
        copySquare(cube, L, 2, 1, B, 2, 1); // L(2, 1) <- B(2, 1)
        copySquare(cube, B, 2, 1, R, 2, 1); // B(2, 1) <- R(2, 1)
        setSquare(cube, R, 2, 1, tmp);      // R(2, 1) <- F(2, 1)
        tmp = getSquare(cube, F, 2, 2);
        copySquare(cube, F, 2, 2, L, 2, 2); // F(2, 2) <- L(2, 2)
        copySquare(cube, L, 2, 2, B, 2, 2); // L(2, 2) <- B(2, 2)
        copySquare(cube, B, 2, 2, R, 2, 2); // B(2, 2) <- R(2, 2)
        setSquare(cube, R, 2, 2, tmp);      // R(2, 2) <- F(2, 2)
        break;
    }
}

static void rotateFaceCounterClockwise(struct rubikCube * cube, unsigned char face) {
    unsigned char i;
    // Rotating conter-clockwise is the same as rotating three times clockwise
    for (i = 0; i < 3; i ++) {
        rotateFaceClockwise(cube, face);
    }
}

void faceRotation(struct rubikCube * cube, char faceName, char directionModifier, char lengthModifier) {

    unsigned char face, i;

    switch (faceName) {
    case 'F':
        face = F;
        break;
    case 'U':
        face = U;
        break;
    case 'R':
        face = R;
        break;
    case 'B':
        face = B;
        break;
    case 'L':
        face = L;
        break;
    case 'D':
        face = D;
        break;
    }

    // Allow any number modifier, not only '2'
    for (i = lengthModifier - '0'; i > 0; i--) {
        if (directionModifier == '\'') {
            rotateFaceCounterClockwise(cube, face);
        } else {
            rotateFaceClockwise(cube, face);
        }
    }
}

void printCube(struct rubikCube * cube) {

    unsigned char face, row, col;

    printf("\n{\n");
    for (face = 0; face < CUBE_FACES; face++) {
        printf("    \"Face %d\": [\n", face);
        for (row = 0; row < FACE_ROWS; row++) {
            printf("        [");
            for (col = 0; col < FACE_COLS; col++) {
                printf("%d", getSquare(cube, face, row, col));
                if (col < FACE_COLS - 1) {
                    printf(", ");
                }
            }
            printf("]");
            if (row < FACE_ROWS - 1) {
                printf(",");
            }
            printf("\n");
        }
        printf("    ]");
        if (face < CUBE_FACES - 1) {
            printf(",");
        }
        printf("\n");
    }
    printf("}\n\n");
}

void initilizeCube(struct rubikCube * cube) {

    unsigned char face, row, col;

    for (face = 0; face < CUBE_FACES; face++) {
        for (row = 0; row < FACE_ROWS; row++) {
            for (col = 0; col < FACE_COLS; col++) {
                setSquare(cube, face, row, col, face);
            }
        }
    }
}
