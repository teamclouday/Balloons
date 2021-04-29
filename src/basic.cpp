#include "basic.hpp"
#include <chrono>

void reshape(int w, int h)
{
    auto engine = GameEngine::instance();
    engine->updateWindowSize(w, h);
}

void renderScene()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto engine = GameEngine::instance();
    engine->renderGame();
    // engine->renderInterface();

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
    float timeInterval = std::chrono::duration_cast<std::chrono::milliseconds>(tEnd - tStart).count();
    float waitInterval = 1.0f / engine->fps * 1000.0f - timeInterval;
    glutTimerFunc((waitInterval > 1) ? static_cast<unsigned int>(waitInterval) : 1, update, value+1);
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