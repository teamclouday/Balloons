#include "basic.hpp"
#include <chrono>

void reshape(int w, int h)
{
    auto engine = GameEngine::instance();
    engine->updateWindowSize(w, h);
}

void renderScene()
{
    glClearColor(91.0f/255.0f, 230.0f/255.0f, 235.0f/255.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto engine = GameEngine::instance();
    engine->renderGame();
    engine->renderInterface();

    glutSwapBuffers();
}

void update(int value)
{
    auto tStart = std::chrono::high_resolution_clock::now();
    auto engine = GameEngine::instance();

    engine->updateLogics(value);
    glutPostRedisplay();
    if(value > engine->fps) value = 0;

    auto tEnd = std::chrono::high_resolution_clock::now();
    unsigned timeInterval = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tStart).count();
    unsigned waitInterval = static_cast<unsigned>(1.0f / engine->fps * 1000.0f) - timeInterval;
    glutTimerFunc((waitInterval > 1) ? waitInterval : 1, update, value+1);
}

void handleKeyboard(unsigned char key, int x, int y)
{
    auto engine = GameEngine::instance();
    engine->handleKeyboard(key);
}

void handleMouseClick(int button, int state, int x, int y)
{
    auto engine = GameEngine::instance();
    if(button == GLUT_LEFT_BUTTON)
    {
        if(state == GLUT_UP) engine->handleMouseClick(false, true);
        else if(state == GLUT_DOWN) engine->handleMouseClick(true, true);
    }
    else if(button == GLUT_RIGHT_BUTTON)
    {
        if(state == GLUT_UP) engine->handleMouseClick(false, false);
        else if(state == GLUT_DOWN) engine->handleMouseClick(true, false);
    }
}

void handleMouseMotion(int x, int y)
{
    auto engine = GameEngine::instance();
    engine->handleMouseMotion(x, y);
}