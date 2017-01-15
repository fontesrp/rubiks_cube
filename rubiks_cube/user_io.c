//
//  user_io.c
//  rubiks_cube
//
//  Created by Rodrigo Fontes on 12/1/17.
//

#include "user_io.h"

static void clearInputStream() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        ;
    }
}

unsigned char getMovementInput(char * faceName, char * directionModifier, char * lengthModifier) {

    // Input must always start with a face name. Optionally, there can be a length and a direction modifier.
    // Exemples of valid inputs: F, U2, B2'

    int c;

    *faceName = '\0';
    *lengthModifier = '1';
    *directionModifier = '\0';

    c = getchar();

    switch (c) {
    case 'F':
    case 'U':
    case 'R':
    case 'B':
    case 'L':
    case 'D':
        *faceName = c;
        break;
    case 'f':
    case 'u':
    case 'r':
    case 'b':
    case 'l':
    case 'd':
        *faceName = c - ('a' - 'A');
        break;
    case '\n':
    case '\r':
    case '\0':
    case EOF:
        return 0;
    default:
        clearInputStream();
        return 0;
    }

    c = getchar();

    if (c >= '0' && c <= '9') {
        *lengthModifier = c;
        c = getchar();
    }

    if (c == '\'') {
        *directionModifier = c;
        clearInputStream();
    } else if (c != '\n' && c != '\r' && c != '\0' && c != EOF) {
        clearInputStream();
        return 0;
    }

    return 1;
}

static unsigned char getRowColors(unsigned char * rowColors) {

    unsigned char color, getAnother, valid = 0, column = 0;

    do {
        color = getchar();
        color = int2color(color);
        switch (color) {
        case 127u:
            if (column == FACE_COLS) {
                // End of valid input
                getAnother = 0;
                valid = 1;
            } else {
                printf("not enough colors\n");
                getAnother = 0;
                valid = 0;
            }
            break;
        case 255u:
            // Invalid char
            printf("invalid color\n");
            clearInputStream();
            getAnother = 0;
            valid = 0;
            break;
        default:
            if (column < FACE_COLS) {
                // set square color
                rowColors[column] = color;
                getAnother = 1;
                column++;
            } else {
                printf("too many colors\n");
                clearInputStream();
                getAnother = 0;
                valid = 0;
            }
            break;
        }
    } while (getAnother);

    return valid;
}

void getCubeInput(struct rubikCube * cube) {

    unsigned char face, row, rowColors[FACE_COLS];

    for (face = F; face <= D; face++) {
        printf("Face %c\n\n", getFaceName(face));
        for (row = 0; row < FACE_ROWS; row++) {
            printf("%d: ", row);
            while (!getRowColors(rowColors)) {
                printf("Invalid input!\n");
                printf("%d: ", row);
            }
            setRowColors(cube, face, row, rowColors);
        }
    }
}
