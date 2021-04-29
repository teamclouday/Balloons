#include "engine.hpp"
#include <GL/freeglut.h>

// render the environment
void GameEngine::renderEnv()
{
    // you will be inside this cylinder
    glFrontFace(GL_CW);
    glColor3f(70.0f/255.0f, 185.0f/255.0f, 189.0f/255.0f);
    glPushMatrix();
    glutSolidSphere(100.0f, 10, 10);
    glPopMatrix();
    glFrontFace(GL_CCW);
    // you will be standing on a box
    glColor3f(189.0f/255.0f, 70.0f/255.0f, 137.0f/255.0f);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    glutSolidCube(10.0f);
    glPopMatrix();
}