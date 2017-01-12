//
//  main.c
//  rubiks_cube
//
//  Created by Rodrigo Fontes on 30/12/16.
//

#include <stdio.h>
#include "rubik_cube.h"
#include "user_io.h"

int main(int argc, const char * argv[]) {
    struct rubikCube cube;
    char faceName, directionModifier, lengthModifier;
    initilizeCube(&cube);
    getCubeInput(&cube);
    printCube(&cube);
    while (1) {
        printf("Enter movement: ");
        while (!getMovementInput(&faceName, &directionModifier, &lengthModifier)) {
            printf("Invalid input!\n");
            printf("Enter movement: ");
        }
        faceRotation(&cube, faceName, directionModifier, lengthModifier);
        printCube(&cube);
    }
    return 0;
}
