#include "engine.hpp"
#include <GL/freeglut.h>

GameEngine::GameEngine()
{
    winW = glutGet(GLUT_WINDOW_WIDTH); // window width
    winH = glutGet(GLUT_WINDOW_HEIGHT); // window height
    viewControl = false; // whether to control the view with cursor
    camera = new Camera(); // init camera object
}

GameEngine::~GameEngine()
{
    if(camera) delete camera;
}

// setup every objects
void GameEngine::setup()
{

}

GameEngine* GameEngine::instance()
{
    static GameEngine engine;
    return &engine;
}

void GameEngine::enterViewControl()
{
    viewControl = true;
    glutSetCursor(GLUT_CURSOR_NONE);
}

void GameEngine::exitViewControl()
{
    viewControl = false;
    glutSetCursor(GLUT_CURSOR_INHERIT);
}

void GameEngine::handleKeyboard(unsigned char key)
{

}