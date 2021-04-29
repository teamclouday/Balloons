#include "engine.hpp"
#include <GL/freeglut.h>
#include <cmath>

// render the environment
void GameEngine::renderEnv()
{
    // you will be inside this cylinder
    const float colorWalls[]{
        244.0f/255.0f, 241.0f/255.0f, 222.0f/255.0f,
        224.0f/255.0f, 122.0f/255.0f, 95.0f/255.0f,
        61.0f/255.0f, 64.0f/255.0f, 91.0f/255.0f,
        129.0f/255.0f, 178.0f/255.0f, 154.0f/255.0f,
        242.0f/255.0f, 204.0f/255.0f, 143.0f/255.0f,
    };
    const int wallSides = 5;
    const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    float wallAngle = 360.0f / wallSides;
    float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    for(int i = 0; i < wallSides; i++)
    {
        glColor3fv(colorWalls + i * 3);
        glPushMatrix();
        glRotatef(wallAngle * i, 0.0f, 1.0f, 0.0f);
        glTranslatef(0.0f, 0.0f, -wallDist);
        glBegin(GL_QUADS);
            glVertex3f(-wallWidth/2.0f, -wallHeight/2.0f, 0.0f);
            glVertex3f(wallWidth/2.0f, -wallHeight/2.0f, 0.0f);
            glVertex3f(wallWidth/2.0f, wallHeight/2.0f, 0.0f);
            glVertex3f(-wallWidth/2.0f, wallHeight/2.0f, 0.0f);
        glEnd();
        glPopMatrix();
    }
    // you will be standing on a box
    glColor3f(189.0f/255.0f, 70.0f/255.0f, 137.0f/255.0f);
    glPushMatrix();
    glTranslatef(0.0f, 5.0f, 0.0f);
    glutSolidCube(10.0f);
    glPopMatrix();
    // this is the ground
    glColor3f(44.0f/255.0f, 156.0f/255.0f, 53.0f/255.0f);
    glBegin(GL_QUADS);
        glVertex3f(-500.0f, -50.0f, -500.0f);
        glVertex3f(-500.0f, -50.0f, 500.0f);
        glVertex3f(500.0f, -50.0f, 500.0f);
        glVertex3f(500.0f, -50.0f, -500.0f);
    glEnd();
    // there will be a sun high up in the sky
    glDisable(GL_LIGHTING);
    glColor3f(252.0f/255.0f, 249.0f/255.0f, 146.0f/255.0f);
    glPushMatrix();
    glTranslatef(-500.0f, 500.0f, -400.0f);
    glutSolidSphere(50.0f, 50, 50);
    glPopMatrix();
    glEnable(GL_LIGHTING);
}