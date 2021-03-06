// render.cpp
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
//      This source file implements all rendering functions for GameEngine class
//      This file also contains functions for ray casting and intersection tests
#include "engine.hpp"
#include <GL/freeglut.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>
#include <sstream>

// render the environment
void GameEngine::renderEnv()
{
    glEnable(GL_LIGHT0);
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
    static float wallAngle = 360.0f / wallSides;
    static float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
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
    glDisable(GL_LIGHT0);
}

void GameEngine::renderGun()
{
    glColor3f(1.0f, 1.0f, 1.0f);
    glEnable(GL_LIGHT1);
    glEnable(GL_TEXTURE_2D);
    gunPos = camera->pos + gunAimD.data * camera->dir + gunAimR.data * camera->right - 2.5f * camera->up;
    glPushMatrix();
    glTranslatef(gunPos.x, gunPos.y, gunPos.z);
    glScalef(0.25f, 0.25f, 0.25f);
    glRotatef(camera->yaw + 90.0f, 0.0f, -1.0f, 0.0f);
    glRotatef(camera->pitch + gunUpDegree.data, 1.0f, 0.0f, 0.0f);
    // select texture to bind
    if(textureActiveID < textures.size() && textures[textureActiveID].second)
        glBindTexture(GL_TEXTURE_2D, textures[textureActiveID].second);
    glBegin(GL_QUADS);
        // left side
        glTexCoord2f(0.00f, 0.10f); glVertex3f(-2.0f, 5.0f, -10.0f);
        glTexCoord2f(0.00f, 0.00f); glVertex3f(-2.0f, 0.0f, -10.0f);
        glTexCoord2f(0.36f, 0.00f); glVertex3f(-2.0f, 0.0f, 8.0f);
        glTexCoord2f(0.36f, 0.10f); glVertex3f(-2.0f, 5.0f, 8.0f);
        // right side
        glTexCoord2f(0.10f, 0.30f); glVertex3f(2.0f, 5.0f, 8.0f);
        glTexCoord2f(0.10f, 0.20f); glVertex3f(2.0f, 0.0f, 8.0f);
        glTexCoord2f(0.46f, 0.20f); glVertex3f(2.0f, 0.0f, -10.0f);
        glTexCoord2f(0.46f, 0.30f); glVertex3f(2.0f, 5.0f, -10.0f);
        // upper side
        glTexCoord2f(0.40f, 0.20f); glVertex3f(2.0f, 5.0f, -10.0f);
        glTexCoord2f(0.40f, 0.10f); glVertex3f(-2.0f, 5.0f, -10.0f);
        glTexCoord2f(0.76f, 0.10f); glVertex3f(-2.0f, 5.0f, 8.0f);
        glTexCoord2f(0.76f, 0.20f); glVertex3f(2.0f, 5.0f, 8.0f);
        // back side
        glTexCoord2f(0.60f, 0.70f); glVertex3f(-2.0f, 5.0f, 8.0f);
        glTexCoord2f(0.60f, 0.60f); glVertex3f(-2.0f, 0.0f, 8.0f);
        glTexCoord2f(0.96f, 0.60f); glVertex3f(2.0f, 0.0f, 8.0f);
        glTexCoord2f(0.96f, 0.70f); glVertex3f(2.0f, 5.0f, 8.0f);
    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0); // bind default texture
    glDisable(GL_TEXTURE_2D);
    // finish other sides
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_QUADS);
        glVertex3f(2.0f, 5.0f, -10.0f);
        glVertex3f(2.0f, 0.0f, -10.0f);
        glVertex3f(-2.0f, 0.0f, -10.0f);
        glVertex3f(-2.0f, 5.0f, -10.0f);
    glEnd();
    glColor3f(0.2f, 0.2f, 0.2f);
    glBegin(GL_QUADS);
        glVertex3f(-2.0f, 0.0f, -10.0f);
        glVertex3f(2.0f, 0.0f, -10.0f);
        glVertex3f(2.0f, 0.0f, 0.0f);
        glVertex3f(-2.0f, 0.0f, 0.0f);
    glEnd();
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.0f, -3.0f, 4.0f);
    glScalef(3.0f/6.0f, 1.0f, 1.0f);
    glutSolidCube(6.0f);
    glPopMatrix();

    glPopMatrix();
    glDisable(GL_LIGHT1);
}

void GameEngine::renderBullets()
{
    glDisable(GL_LIGHTING);
    glPointSize(5.0f);
    glBegin(GL_POINTS);
    glColor3f(0.2f, 0.2f, 0.2f);
    for(auto& pos : bullets.data)
        glVertex3f(pos.pos.x, pos.pos.y, pos.pos.z);
    glEnd();
    glEnable(GL_LIGHTING);
}

void GameEngine::renderBalloons()
{
    glEnable(GL_LIGHT0);
    for(auto& balloon : balloons->balloons)
    {
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_COLOR);
        // inner sphere to create solid feeling
        switch(balloon.color)
        {
            case ParticleBalloon::BallonColor::RED:
                glColor4f(235.0f/255.0f, 64.0f/255.0f, 52.0f/255.0f, 0.8f);
                break;
            case ParticleBalloon::BallonColor::BLUE:
                glColor4f(52.0f/255.0f, 128.0f/255.0f, 235.0f/255.0f, 0.8f);
                break;
            case ParticleBalloon::BallonColor::GREEN:
                glColor4f(55.0f/255.0f, 235.0f/255.0f, 52.0f/255.0f, 0.8f);
                break;
            case ParticleBalloon::BallonColor::PINK:
                glColor4f(242.0f/255.0f, 80.0f/255.0f, 226.0f/255.0f, 0.8f);
                break;
            case ParticleBalloon::BallonColor::YELLOW:
                glColor4f(242.0f/255.0f, 221.0f/255.0f, 80.0f/255.0f, 0.8f);
                break;
            default: break;
        }
        glPushMatrix();
        glTranslatef(balloon.pos.x, balloon.pos.y, balloon.pos.z);
        glutSolidSphere(balloon.radius * 0.8f, 20, 20);
        glPopMatrix();

        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_DST_COLOR);
        glPushMatrix();
        glTranslatef(balloon.pos.x, balloon.pos.y, balloon.pos.z);
        glutSolidSphere(balloon.radius, 20, 20);
        glPopMatrix();
    }
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glDisable(GL_LIGHT0);
}

void GameEngine::renderFireworks()
{
    glDisable(GL_LIGHTING);
    glPointSize(3.0f);
    float alpha;
    for(auto firework : fireworks)
    {
        alpha = 1.0f;
        if(firework->timeout < fps) alpha = 0.75f;
        if(firework->timeout < fps / 2) alpha = 0.5f;
        if(firework->timeout < fps / 4) alpha = 0.25f;
        if(firework->timeout < 5) alpha = 0.1f;
        glColor4f(firework->color.r, firework->color.g, firework->color.b, alpha);
        glBegin(GL_POINTS);
        for(auto& particle : firework->particles)
            glVertex3fv(&particle->pos[0]);
        glEnd();
    }
    glEnable(GL_LIGHTING);
}



bool isIntersectTriangle(const glm::vec3& origin, const glm::vec3& dir, float& t,
                        glm::vec3 v0, glm::vec3 v1, glm::vec3 v2)
{
    // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/ray-triangle-intersection-geometric-solution
    // glm::vec3 edge0 = v1 - v0;
    // glm::vec3 edge1 = v2 - v1;
    // glm::vec3 edge2 = v0 - v2;
    // glm::vec3 N = glm::cross(v1-v0, v2-v0); // compute normal
    // float D = glm::dot(N, v1); // compute distance
    // float checked = glm::dot(N, dir); // check for parallel
    // if(std::abs(checked) <= 0.01f) return false;
    // t = (glm::dot(N, origin) + D) / checked;
    // if(t < 0.0f) return false; // check if is behind the ray
    // glm::vec3 hitPos = origin + t * dir;
    // // check if is outside the triangle
    // if(glm::dot(N, glm::cross(edge0, hitPos-v0)) >= 0.0f &&
    //    glm::dot(N, glm::cross(edge1, hitPos-v1)) >= 0.0f &&
    //    glm::dot(N, glm::cross(edge2, hitPos-v2)) >= 0.0f)
    //    return true; // this means it is inside triangle
    // return false;


    // a faster implementation
    // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-rendering-a-triangle/moller-trumbore-ray-triangle-intersection
    glm::vec3 pvec = glm::cross(dir, v2-v0);
    float det = glm::dot(v1-v0, pvec);
    if(det < 0.01f) return false;
    float invDet = 1.0f / det;
    glm::vec3 tvec = origin - v0;
    float u = glm::dot(tvec, pvec) * invDet;
    if(u < 0.0f || u > 1.0f) return false;
    glm::vec3 qvec = glm::cross(tvec, v1-v0);
    float v = glm::dot(dir, qvec) * invDet;
    if(v < 0.0f || u + v > 1.0f) return false;
    t = glm::dot(v2-v0, qvec) * invDet;
    return true;
}

bool isIntersectSphere(const glm::vec3& origin, const glm::vec3& dir, float& t,
                        glm::vec3 center, float radius)
{
    // reference: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
    glm::vec3 L = origin-center;
    float a = glm::dot(dir, dir);
    float b = 2.0f * glm::dot(dir, L);
    float c = glm::dot(L, L) - radius * radius;
    float delta = b*b - 4.0f * a * c;
    float t0 = (-b + std::sqrt(delta)) / (2.0f * a);
    float t1 = (-b - std::sqrt(delta)) / (2.0f * a);
    // no need to set hitpos because balloon will explode
    if(delta > 0.0f)
    {
        if(t0 > 0.0f && t1 > 0.0f)
        {
            t = std::min(t0, t1);
            return true;
        }
    }
    else if(delta == 0.0f) 
    {
        t = t0;
        return true;
    }
    return false;
}

// cast a gun shot and get first hit position
// this function is written in render.cpp because it requires all data defined here
bool GameEngine::raycast(const glm::vec3& origin, const glm::vec3& dir, float& t)
{
    float minT = 10000.0f; // set current minimum distance
    // check for environment
    const int wallSides = 5;
    const float wallHeight = 100.0f;
    const float wallWidth = 500.0f;
    static float wallAngle = 360.0f / wallSides;
    static float wallDist = wallWidth / 2.0f * 1.0f / std::tan(glm::radians(wallAngle / 2.0f));
    for(int i = 0; i < wallSides; i++)
    {
        float localT = 0.0f;
        glm::vec3 v0, v1, v2;
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(wallAngle * i), glm::vec3(0.0f, 1.0f, 0.0f)) *
            glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -wallDist));
        v0 = glm::vec3(transform * glm::vec4(-wallWidth/2.0f, -wallHeight/2.0f, 0.0f, 1.0f));
        v1 = glm::vec3(transform * glm::vec4(wallWidth/2.0f, -wallHeight/2.0f, 0.0f, 1.0f));
        v2 = glm::vec3(transform * glm::vec4(wallWidth/2.0f, wallHeight/2.0f, 0.0f, 1.0f));
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
        v1 = v2;
        v2 = glm::vec3(transform * glm::vec4(-wallWidth/2.0f, wallHeight/2.0f, 0.0f, 1.0f));
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
    }
    {
        float localT = 0.0f;
        glm::vec3 v0, v1, v2;
        v0 = glm::vec3(-5.0f, 10.0f, -5.0f);
        v1 = glm::vec3(-5.0f, 10.0f, 5.0f);
        v2 = glm::vec3(5.0f, 10.0f, 5.0f);
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
        v1 = v2;
        v2 = glm::vec3(5.0f, 10.0f, -5.0f);
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
    }
    {
        float localT = 0.0f;
        glm::vec3 v0, v1, v2;
        v0 = glm::vec3(-500.0f, -50.0f, -500.0f);
        v1 = glm::vec3(-500.0f, -50.0f, 500.0f);
        v2 = glm::vec3(500.0f, -50.0f, 500.0f);
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
        v1 = v2;
        v2 = glm::vec3(500.0f, -50.0f, -500.0f);
        if(isIntersectTriangle(origin, dir, localT, v0, v1, v2))
            if(localT < minT) minT = localT;
    }

    // find nearest balloon hit
    auto toExplode = balloons->balloons.end();
    float bT = 10000.0f;
    for(auto iter = balloons->balloons.begin(); iter != balloons->balloons.end(); iter++)
    {
        float localbT = 0.0f;
        if(isIntersectSphere(origin, dir, localbT, iter->pos, iter->radius))
        {
            if(localbT < bT)
            {
                bT = localbT;
                toExplode = iter;
            }
        }
    }
    // check if balloon is the nearest target hit
    if(toExplode != balloons->balloons.end() && bT < minT)
    {
        bool checkRest = false;
        if(state <= GameState::BEGINNING_SHOOT)
        {
            score += 1;
            totalShotsCorrect++;
        }
        switch(state)
        {
            case GameState::STAGE1:
            {
                score++;
                totalShotsCorrect++;
                break;
            }
            case GameState::STAGE2:
            {
                if(toExplode->color == ParticleBalloon::BallonColor::GREEN)
                {
                    score++;
                    checkRest = true;
                    totalShotsCorrect++;
                }
                else
                {
                    addHelpMessage("Wrong color hit", 2 * fps);
                    score -= 2;
                }
                break;
            }
            case GameState::STAGE3:
            {
                score++;
                totalShotsCorrect++;
                break;
            }
            case GameState::STAGE4:
            {
                if(toExplode->color == ParticleBalloon::BallonColor::GREEN)
                {
                    score++;
                    totalShotsCorrect++;
                    checkRest = true;
                }
                else
                {
                    addHelpMessage("Wrong color hit", 2 * fps);
                    score -= 2;
                }
                break;
            }
            default: break;
        }
        // start a small firework at the balloon location
        fireworks.push_back(new Firework(
            50, 3 * fps, toExplode->radius * 2.0f, toExplode->pos
        ));
        // then remove the balloon
        balloons->balloons.erase(toExplode);
        if(checkRest)
        {
            int count = 0;
            for(auto iter = balloons->balloons.begin(); iter != balloons->balloons.end(); iter++)
            {
                if(iter->color == ParticleBalloon::BallonColor::GREEN) count++;
            }
            if(count <= 0)
            {
                if(state == GameState::STAGE2)
                {
                    state = GameState::STAGE3;
                    balloons->loadBalloonsStage3();
                    gameGuide = "#3 Shoot all balloons in the sky!";
                }
                if(state == GameState::STAGE4)
                {
                    if(score >= 0) 
                    {
                        state = GameState::WIN;
                        enterEndWin();
                    }
                }
            }
        }
        return false; // return no hit so that no new bullet is added
    }
    else
    {
        if(state >= GameState::STAGE1)
        {
            // addHelpMessage("Missed shot", 1 * fps);
            score--;
        }
    }

    if(minT < 10000.0f) 
    {
        t = minT;
        return true;
    }
    return false;
}

void GameEngine::renderEndWin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, winW, 0.0f, winH, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    std::string message = "You Win!";
    glPushMatrix();
    glTranslatef(winW / 2.0f - message.size() / 2.0f * 60.0f, winH - 120.0f, 0.5f);
    glScalef(0.6f, 0.6f, 1.0f);
    glLineWidth(2.0f);
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(char& ch : message) glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ch);
    glPopAttrib();
    glPopMatrix();

    std::stringstream sstr1;
    sstr1 << "Total Score: " << score;
    std::stringstream sstr2;
    sstr2 << "Total Shots: " << totalShots;
    std::stringstream sstr3;
    sstr3 << "Total Correct Shots: " << totalShotsCorrect;

    static std::vector<std::string> thanks{
        "", "", "",
        sstr1.str(), "",
        sstr2.str(), "",
        sstr3.str(), "",
        "", "",
        "Game Engine", "",
        "Sida Zhu", "", "",
        "Logics Design", "",
        "Sida Zhu", "", "",
        "Animation Design", "",
        "Sida Zhu", "", "",
        "Artistic Effects", "",
        "Sida Zhu", "", "",
        "Chief Programmer", "",
        "Sida Zhu", "", "",
        "Market Promotion", "",
        "Sida Zhu", "", "", "", "",
        "Special Thanks", "",
        "Dr. Baruch (Instructor)",
        "Tianyi Wu (Tester)",
        "Chang Liu (Tester)",
    };

    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(unsigned line = 0; line < thanks.size(); line++)
    {
        auto& str = thanks[line];
        glRasterPos3f(winW / 2.0f - str.size() / 2.0f * 10.0f, endWinMessageScroll + winH / 2.0f - line * 30.0f, -0.5f);
        for(auto& ch : str) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, ch);
    }
    glPopAttrib();

    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_QUADS);
        glVertex3f(0.0f, winH, 0.0f);
        glVertex3f(0.0f, winH - 200.0f, 0.0f);
        glVertex3f(winW, winH - 200.0f, 0.0f);
        glVertex3f(winW, winH, 0.0f);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (float)winW / (float)winH, 0.1f, 1000.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0f, 50.0f, -50.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    if(endWinMessageScroll < (thanks.size() + 2) * 30.0f)
        endWinMessageScroll += 0.8f;
}

void GameEngine::renderEndLose()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, winW, 0.0f, winH, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    if(textureLossSpecial) glBindTexture(GL_TEXTURE_2D, textureLossSpecial);
    glPushMatrix();
    float imageWidth = 0.8f * winW / 2.0f;
    float imageHeight = imageWidth / 400.0f * 225.0f;
    glTranslatef(winW / 2.0f, winH / 1.5f, 0.0f);
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex3f(-imageWidth/2.0f, imageHeight/2.0f, -0.5f);
        glTexCoord2f(0.0f, 0.0f); glVertex3f(-imageWidth/2.0f, -imageHeight/2.0f, -0.5f);
        glTexCoord2f(1.0f, 0.0f); glVertex3f(imageWidth/2.0f, -imageHeight/2.0f, -0.5f);
        glTexCoord2f(1.0f, 1.0f); glVertex3f(imageWidth/2.0f, imageHeight/2.0f, -0.5f);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    std::string message = "You Loss!";
    glPushMatrix();
    glTranslatef(winW / 2.0f - message.size() / 2.0f * 60.0f, 100.0f, 0.5f);
    glScalef(0.6f, 0.6f, 1.0f);
    glLineWidth(2.0f);
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1.0f, 1.0f, 1.0f);
    for(char& ch : message) glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN, ch);
    glPopAttrib();
    glPopMatrix();
}