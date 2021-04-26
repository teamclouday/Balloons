// This header file declares most functions used in main.cpp
#pragma once

#include "GL/freeglut.h"

// setup OpenGL features, as well as loading all objects
void setup();
// render a frame
void renderScene();
// fps control and logic updates
void update(int value);
// handle keyboard inputs
void handleKeyboard(unsigned char key, int x, int y);