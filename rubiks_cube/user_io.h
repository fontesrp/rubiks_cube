//
//  user_io.h
//  rubiks_cube
//
//  Created by Rodrigo Fontes on 12/1/17.
//

#ifndef user_io_h
#define user_io_h

#include <stdio.h>
#include "rubik_cube.h"

unsigned char getMovementInput(char * faceName, char * directionModifier, char * lengthModifier);
void getCubeInput(struct rubikCube * cube);

#endif // user_io_h
