// basic.hpp
// Assignment: CIS425 Final Project
// Environment/Compiler:
//                  Visual Studio Community 2019 (Tested)
//                  Linux GCC (Tested)
//                  MacOS GCC (Not Tested)
// Date: May 14, 2021
// Official Name:  Sida Zhu
// E-mail:
//      szhu28@syr.edu
//      teamclouday@gmail.com
// File Description:
//      This header file declares most functions used in main.cpp for glut callbacks
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