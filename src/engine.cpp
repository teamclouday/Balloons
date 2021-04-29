#include "engine.hpp"
#include <GL/freeglut.h>
#include <cstdlib>
#include <ctime>

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
    // setup OpenGL features
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

    const float matSpec[]{1.0f, 1.0f, 1.0f, 1.0f};
    const float globAmb[]{0.2f, 0.2f, 0.2f, 1.0f};
    const float matShine[]{50.0f};
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, matShine);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);

    // setup lights
    const float colorAmbient[]{0.0f, 0.0f, 0.0f, 0.0f};
    const float colorWhiteLight[]{0.8f, 0.8f, 0.8f, 1.0f};
    const float posLight0[]{0.0f, 95.0f, 0.0f, 1.0f};
    glEnable(GL_LIGHT0); // light0 is above the head of the camera
    glLightfv(GL_LIGHT0, GL_AMBIENT, colorAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, colorWhiteLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, colorWhiteLight);
    glLightfv(GL_LIGHT0, GL_POSITION, posLight0);

    // setup camera
    camera->pos = glm::vec3(0.0f, 20.0f, 0.0f);
    camera->worldUP = glm::vec3(0.0f, 1.0f, 0.0f);
    camera->pitch = 0.0f;
    camera->yaw = -90.0f;
    camera->rotVel = 1.0f / fps * 5.0f;
    camera->update();

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
        auto nextIter = textIter + 1;
        textIter->second--;
        if(textIter->second < 0) helpMessage.erase(textIter);
        textIter = nextIter;
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
        std::cout << camera->pitch << std::endl;
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
        int lineCounter = 0;
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
            auto text = helpMessage[i].first;
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
            }
            break;
        }
        default: break;
    }
}

void GameEngine::handleMouseClick(bool isDown, bool isLeft)
{
    if(!viewControl) return;

}

void GameEngine::handleMouseMotion(int x, int y)
{
    if(!viewControl) return;
    mouseX = x;
    mouseY = y;
}

void GameEngine::addHelpMessage(const std::string message, unsigned timeout)
{
    helpMessage.push_back(std::make_pair(message, timeout));
}