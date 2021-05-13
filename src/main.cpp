#include "basic.hpp"

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Balloon Shooter");
    // first time init game engine object
    auto engine = GameEngine::instance();
    engine->setup();
    glutDisplayFunc(renderScene);
    glutKeyboardFunc(handleKeyboard);
    glutReshapeFunc(reshape);
    glutMouseFunc(handleMouseClick);
    glutMotionFunc(handleMouseMotion);
    glutPassiveMotionFunc(handleMouseMotion);
    glutTimerFunc(1, update, 1);
    glutMainLoop();
    return 0;
}