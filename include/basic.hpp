// This header file declares most functions used in main.cpp
#pragma once

#include <GL/freeglut.h>
#include "engine.hpp"

// reshape window
void reshape(int w, int h);
// render a frame
void renderScene();
// fps control and logic updates
void update(int value);
// handle keyboard inputs
void handleKeyboard(unsigned char key, int x, int y);
// handle mouse click
void handleMouseClick(int button, int state, int x, int y);
// handle mouse motion
void handleMouseMotion(int x, int y);