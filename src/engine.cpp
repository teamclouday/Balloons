#include "engine.hpp"
#include <GL/freeglut.h>

GameEngine::GameEngine()
{
    winW = glutGet(GLUT_WINDOW_WIDTH); // window width
    winH = glutGet(GLUT_WINDOW_HEIGHT); // window height
    viewControl = false; // whether to control the view with cursor
    helpMessage.resize(0); // The help message on the upper left corner of the screen
    camera = new Camera(); // init camera object
}

GameEngine::~GameEngine()
{
    if(camera) delete camera;
}

// setup every objects
void GameEngine::setup()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);


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

void GameEngine::updateLogics(int frameNum)
{

}

void GameEngine::renderGame()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, (float)winW / (float)winH, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glm::vec3 viewCenter = camera->pos + camera->dir;
    gluLookAt(
        camera->pos.x, camera->pos.y, camera->pos.z,
        viewCenter.x, viewCenter.y, viewCenter.z,
        camera->up.x, camera->up.y, camera->up.z
    );

}

void GameEngine::renderInterface()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-winW/2.0f, winW/2.0f, -winH/2.0f, winH/2.0f, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(helpMessage.size() > 0)
    {
        int length = helpMessage.size();
        glPushMatrix();
        glTranslatef(0.0f, winH / 2.0f - 50.0f, 0.0f);
        glColor3f(0.2f, 0.2f, 0.2f);
        glBegin(GL_QUADS);
        glVertex2f(length / 2.0f * 10.0f, 15.0f);
        glVertex2f(-length / 2.0f * 10.0f, 15.0f);
        glVertex2f(-length / 2.0f * 10.0f, -5.0f);
        glVertex2f(length / 2.0f * 10.0f, -5.0f);
        glEnd();
        glPopMatrix();
        for(unsigned i = 0; i < helpMessage.size(); i++)
        {
            auto text = helpMessage[i];
            glPushMatrix();
            glPushAttrib(GL_CURRENT_BIT);
            glColor3f(1.0f, 1.0f, 1.0f);
            glRasterPos2f(-length / 2.0f * 9.0f, 0.0f);
            for(char& c : text) glutBitmapCharacter(GLUT_BITMAP_9_BY_15, c);
            glPopAttrib();
            glPopMatrix();
        }
    }
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void GameEngine::updateWindowSize(int w, int h)
{
    winW = w;
    winH = h;
    glViewport(0, 0, winW, winH);
}

void GameEngine::handleKeyboard(unsigned char key)
{

}