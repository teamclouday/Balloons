#include "engine.hpp"
#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

GameEngine::GameEngine()
{
    winW = glutGet(GLUT_WINDOW_WIDTH); // window width
    winH = glutGet(GLUT_WINDOW_HEIGHT); // window height
    viewControl = false; // whether to control the view with cursor
    helpMessage.resize(0); // The help message on the upper left corner of the screen
    camera = new Camera(); // init camera object
    audioEngine = irrklang::createIrrKlangDevice(); // init irrklang audio engine
    balloons = new ParticleBalloon(); // load balloon manager
}

GameEngine::~GameEngine()
{
    if(camera) delete camera;
    if(balloons) delete balloons;
    for(auto& data : fireworks) delete data;
    for(auto& pair : textures) if(pair.second) glDeleteTextures(1, &pair.second);
    if(musicBackground) musicBackground->drop();
    if(audioEngine) audioEngine->drop();
}

// setup every objects
void GameEngine::setup()
{
    // setup OpenGL features
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    // const float matSpec[]{0.8f, 0.8f, 0.8f, 1.0f};
    const float globAmb[]{0.2f, 0.2f, 0.2f, 1.0f};
    const float matShine[]{50.0f};
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // setup lights
    const float colorAmbient[]{0.0f, 0.0f, 0.0f, 0.0f};
    const float colorWhiteLight[]{0.8f, 0.8f, 0.8f, 1.0f};
    const float colorDarkLight[]{0.8f, 0.8f, 0.8f, 1.0f};
    const float posLight0[]{0.0f, 500.0f, 0.0f, 1.0f};
    const float posLight1[]{0.0f, 20.0f, 0.0f, 1.0f};
    // light0 is the directional light for the sun
    glLightfv(GL_LIGHT0, GL_AMBIENT, colorAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, colorWhiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, colorWhiteLight);
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);
    // light1 is for better gun model view
    glLightfv(GL_LIGHT1, GL_AMBIENT, colorAmbient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, colorDarkLight);
    glLightfv(GL_LIGHT1, GL_SPECULAR, colorDarkLight);
    glLightfv(GL_LIGHT1, GL_POSITION, posLight1);

    // setup camera
    camera->pos = glm::vec3(0.0f, 20.0f, 0.0f);
    camera->worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
    camera->pitch = 0.0f;
    camera->yaw = -90.0f;
    camera->rotVel = 1.0f / fps * 4.0f;
    camera->update();

    // setup starting help messages
    addHelpMessage("Fullscreen view is recommended", 5 * fps);
    addHelpMessage("Press SPACE to enter view control mode", 8 * fps);

    // load textures for gun
    textures.push_back({"assets/pexels-aleksandr-slobodianyk-989946.jpg", 0});
    textures.push_back({"assets/pexels-anni-roenkae-2832432.jpg", 0});
    textures.push_back({"assets/pawel-czerwinski-gKUqBsolYq0-unsplash.jpg", 0});
    textures.push_back({"assets/christian-holzinger-CUY_YHhCFl4-unsplash.jpg", 0});
    textures.push_back({"assets/lucas-benjamin-wQLAGv4_OYs-unsplash.jpg", 0});
    loadTextures();
    textureActiveID = 0;
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    // setup audio engine
    if(!audioEngine) 
    {
        addHelpMessage("Audio engine failed to load, no sound will be available", 5 * fps);
        std::cout << "Audio engine failed to load, no sound will be available" << std::endl;
    }
    musicBackground = audioEngine->play2D("assets/bensound-happyrock.mp3", true, false, true);
    if(musicBackground) musicBackground->setVolume(0.4f);

    // setup game states
    state = GameState::BEGINNING;
    balloons->loadBalloonsBegin();

    srand(time(0));
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
    // wrap cursor to the center
    glutWarpPointer(winW/2, winH/2);
}

void GameEngine::exitViewControl()
{
    viewControl = false;
    glutSetCursor(GLUT_CURSOR_INHERIT);
}

void GameEngine::updateLogics(int frameNum)
{
    // update help messages
    auto textIter = helpMessage.begin();
    while(textIter != helpMessage.end())
    {
        textIter->second--;
        if (textIter->second < 0)
            textIter = helpMessage.erase(textIter);
        else textIter++;
    }
    // update cursor information
    if(viewControl)
    {
        int deltaX = mouseX - winW/2;
        int deltaY = mouseY - winH/2;
        camera->changeView(deltaX, deltaY);
        camera->update();
        glutWarpPointer(winW/2, winH/2);
        mouseX = winW/2;
        mouseY = winH/2;
    }
    // update gun postion
    switch(gunUpDegree.state)
    {
        case AnimState::FORWARD:
        {
            gunUpDegree.data += gunUpDegree.step;
            if(gunUpDegree.data >= gunUpDegree.end)
            {
                gunUpDegree.data = gunUpDegree.end;
                gunUpDegree.state = AnimState::BACKWARD;
            }
            break;
        }
        case AnimState::BACKWARD:
        {
            gunUpDegree.data -= gunUpDegree.step;
            if(gunUpDegree.data <= gunUpDegree.start)
            {
                gunUpDegree.data = gunUpDegree.start;
                gunUpDegree.state = AnimState::DEFAULT;
            }
            break;
        }
        default: break;
    }
    // update gun aim data
    switch(gunAimR.state)
    {
        case AnimState::FORWARD:
        {
            gunAimR.data += gunAimR.step;
            if(gunAimR.data >= gunAimR.end)
            {
                gunAimR.data = gunAimR.end;
                gunAimR.state = AnimState::DEFAULT;
            }
            break;
        }
        case AnimState::BACKWARD:
        {
            gunAimR.data -= gunAimR.step;
            if(gunAimR.data <= gunAimR.start)
            {
                gunAimR.data = gunAimR.start;
                gunAimR.state = AnimState::DEFAULT;
            }
            break;
        }
        default: break;
    }
    switch(gunAimD.state)
    {
        case AnimState::FORWARD:
        {
            gunAimD.data += gunAimD.step;
            if(gunAimD.data >= gunAimD.end)
            {
                gunAimD.data = gunAimD.end;
                gunAimD.state = AnimState::DEFAULT;
            }
            break;
        }
        case AnimState::BACKWARD:
        {
            gunAimD.data -= gunAimD.step;
            if(gunAimD.data <= gunAimD.start)
            {
                gunAimD.data = gunAimD.start;
                gunAimD.state = AnimState::DEFAULT;
            }
            break;
        }
        default: break;
    }
    // update traced bullets
    bullets.update();
    // update balloons
    if(balloons) balloons->update(fps);
    // update fireworks
    auto fireIter = fireworks.begin();
    while(fireIter != fireworks.end())
    {
        (*fireIter)->update(fps);
        if((*fireIter)->timeout < 0)
        {
            auto savedPtr = *fireIter;
            fireIter = fireworks.erase(fireIter);
            delete savedPtr;
        }
        else fireIter++;
    }
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

    // render every objects
    renderEnv();
    renderGun();
    renderBullets();
    renderBalloons();
    renderFireworks();
}

void GameEngine::renderInterface()
{
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, winW, 0.0f, winH, -1.0f, 1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(helpMessage.size() > 0)
    {
        int lineCounter = 0;
        int charCounter = 0;
        const int maxCharInLine = 45;
        glPushAttrib(GL_CURRENT_BIT);
        glColor3f(1.0f, 1.0f, 1.0f);
        for(auto& message : helpMessage)
        {
            lineCounter++;
            charCounter = 0;
            glRasterPos3f(10.0f, winH - lineCounter * 20.0f, 0.5f);
            for(char& ch : message.first)
            {
                charCounter++;
                glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ch);
                if(charCounter > maxCharInLine) 
                {
                    lineCounter++;
                    glRasterPos3f(10.0f, winH - lineCounter * 20.0f, 0.5f);
                    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '-');
                    charCounter = 0;
                }
            }
        }
        glPopAttrib();
        // next draw background with some transparency
        glColor4f(0.2f, 0.2f, 0.2f, 0.8f);
        glBegin(GL_QUADS);
            glVertex3f(5.0f, winH - 5.0f, -0.5f);
            glVertex3f(5.0f, winH - lineCounter * 20.0f - 5.0f, -0.5f);
            glVertex3f(10.0f + 10.0f * (maxCharInLine - 1), winH - lineCounter * 20.0f - 5.0f, -0.5f);
            glVertex3f(10.0f + 10.0f * (maxCharInLine - 1), winH - 5.0f, -0.5f);
        glEnd();
    }
    // TODO: render game guide in upper middle screen

    // next render center crosshair
    glDisable(GL_DEPTH_TEST);
    glLineWidth(5.0f);
    glColor3f(28.0f/255.0f, 61.0f/255.0f, 29.0f/255.0f);
    glBegin(GL_LINES);
        glVertex2f(winW/2.0f-15.0f, winH/2.0f);
        glVertex2f(winW/2.0f+15.0f, winH/2.0f);
        glVertex2f(winW/2.0f, winH/2.0f-15.0f);
        glVertex2f(winW/2.0f, winH/2.0f+15.0f);
    glEnd();
    glLineWidth(3.0f);
    glColor3f(4.0f/255.0f, 209.0f/255.0f, 8.0f/255.0f);
    glBegin(GL_LINES);
        glVertex2f(winW/2.0f-14.0f, winH/2.0f);
        glVertex2f(winW/2.0f+14.0f, winH/2.0f);
        glVertex2f(winW/2.0f, winH/2.0f-14.0f);
        glVertex2f(winW/2.0f, winH/2.0f+14.0f);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
}

void GameEngine::updateWindowSize(int w, int h)
{
    winW = w;
    winH = h;
    glViewport(0, 0, winW, winH);
}

void GameEngine::handleKeyboard(unsigned char key)
{
    switch(key)
    {
        case 27:
        {
            if(viewControl)
            {
                exitViewControl();
                addHelpMessage("You have exit control mode, press ESC again to quit", 5 * fps);
            }
            else
                exit(0);
            break;
        }
        case ' ':
        {
            if(!viewControl)
            {
                enterViewControl();
                addHelpMessage("You have entered control mode, press ESC to exit", 5 * fps);
                addHelpMessage("LEFT click to shoot, RIGHT click and hold to aim", 5 * fps);
            }
            break;
        }
        default: break;
    }
    if(key >= '1' && key <= '9')
    {
        for(unsigned i = 0; i < textures.size(); i++)
        {
            if(key == '1' + static_cast<unsigned char>(i))
            {
                if(textures[i].second && textureActiveID != i)
                {
                    textureActiveID = i;
                    std::stringstream sstr;
                    sstr << "You have switched to texture " << i + 1;
                    addHelpMessage(sstr.str(), 5 * fps);
                }
                break;
            }
        }
    }
}

void GameEngine::handleMouseClick(bool isDown, bool isLeft)
{
    if(!viewControl) return;
    if(isLeft && isDown && gunUpDegree.data > gunUpDegree.end / 3.0f) return; // at this point, the gun is not ready to shoot
    if(isLeft && isDown)
    {
        gunUpDegree.state = AnimState::FORWARD; // gun going up
        audioEngine->play2D("assets/12-Gauge-Pump-Action-Shotgun-Close-Gunshot-A-www.fesliyanstudios.com.mp3"); // play sound effect
        // trace bullet
        float t = 0.0f;
        auto pos = camera->pos;
        if(gunAimR.data != gunAimR.start)
        {
            // add some randomness to the shot
            pos += (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f) * 10.0f * camera->right + 
                (static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * 2.0f - 1.0f) * 10.0f * camera->up;
        }

        if(trace(pos, camera->dir, t))
        {
            // std::cout << "ray hit " << t << std::endl;
            auto newPos = pos + (t - 0.5f) * camera->dir;
            bullets.addBullet(newPos, 20 * fps);
        }
    }
    if(!isLeft)
    {
        if(isDown)
        {
            gunAimD.state = AnimState::BACKWARD;
            gunAimR.state = AnimState::BACKWARD;
        }
        else
        {
            gunAimD.state = AnimState::FORWARD;
            gunAimR.state = AnimState::FORWARD;
        }
    }
}

void GameEngine::handleMouseMotion(int x, int y)
{
    if(!viewControl) return;
    mouseX = x;
    mouseY = y;
}

void GameEngine::addHelpMessage(const std::string message, int timeout)
{
    helpMessage.push_back(std::make_pair(message, timeout));
}

void GameEngine::loadTextures()
{
    int width, height, channels;
    unsigned char* data;
    for(auto& pair : textures)
    {
        data = stbi_load(pair.first.c_str(), &width, &height, &channels, STBI_rgb);
        if(data)
        {
            glGenTextures(1, &pair.second);
            glBindTexture(GL_TEXTURE_2D, pair.second);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            stbi_image_free(data);
        }
        else
        {
            std::stringstream sstr;
            sstr << "Failed to load image: " << pair.first;
            addHelpMessage(sstr.str(), 5 * fps);
            std::cout << "Failed to load image: " << pair.first << std::endl;
            std::cout << "stb_image error: " << stbi_failure_reason() << std::endl;
        }
    }
}