/*
 *  main.cpp  –  Entry point, GLUT callbacks, projection setup
 *
 *  Assignment 1 - 2D Mini Arcade Game: Space Shooter (Static Scene)
 *  ----------------------------------------------------------------
 *  4 Main Objects (4 team members):
 *    1. Spaceship   (Player)      – Spaceship.cpp  Z = -1
 *    2. Alien Enemy (Enemy)       – Alien.cpp      Z = -3
 *    3. Asteroid    (Hazard)      – Asteroid.cpp   Z = -2
 *    4. Planet      (Background)  – Background.cpp Z = -5
 *
 *  Controls:
 *    O / o   -> Orthographic Projection
 *    P / p   -> Perspective  Projection
 *    ESC     -> Exit
 */

#include <GL/glew.h>
#include <GL/glut.h>
#include <cstdio>

#include "Spaceship.h"
#include "Alien.h"
#include "Asteroid.h"
#include "Background.h"
#include "HUD.h"

 // ---------------------------------------------------------------
 //  Constants
 // ---------------------------------------------------------------
static const int   WIN_W = 800;
static const int   WIN_H = 600;
static const float ASPECT = static_cast<float>(WIN_W) / WIN_H;

// ---------------------------------------------------------------
//  Global state
// ---------------------------------------------------------------
static bool usePerspective = false;   // start with orthographic

// ---------------------------------------------------------------
//  Projection helpers
// ---------------------------------------------------------------
static void applyOrthographic()
{
    glOrtho(-1.0, 1.0, -1.0, 1.0, 0.1, 100.0);
}

static void applyPerspective()
{
    gluPerspective(60.0, ASPECT, 0.1, 100.0);
}

static void setupProjection()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if (usePerspective)
        applyPerspective();
    else
        applyOrthographic();
}

static void setupCamera()
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 1.0,      // eye
        0.0, 0.0, 0.0,      // center
        0.0, 1.0, 0.0);     // up
}

// ---------------------------------------------------------------
//  GLUT display callback
// ---------------------------------------------------------------
static void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    setupProjection();
    setupCamera();

    // Draw scene layers (back to front)
    drawBackground();      // Z = -5  (farthest)
    drawAlien();           // Z = -3  (enemy)
    drawAsteroid();        // Z = -2  (hazard, left & right sides)
    drawSpaceship();       // Z = -1  (closest / player)

    // HUD overlay
    if (usePerspective)
        drawText(10, 575, "Projection: PERSPECTIVE  (press O for Ortho)");
    else
        drawText(10, 575, "Projection: ORTHOGRAPHIC (press P for Persp)");

    drawText(10, 10, "Space Shooter - 2D Arcade Scene  |  ESC to exit");

    glutSwapBuffers();
}

// ---------------------------------------------------------------
//  GLUT keyboard callback
// ---------------------------------------------------------------
static void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    switch (key) {
    case 'o': case 'O':
        usePerspective = false;
        printf("[Key] Switched to ORTHOGRAPHIC projection\n");
        break;
    case 'p': case 'P':
        usePerspective = true;
        printf("[Key] Switched to PERSPECTIVE projection\n");
        break;
    case 27:
        printf("[Key] ESC pressed – exiting\n");
        exit(0);
        break;
    }
    glutPostRedisplay();
}

// ---------------------------------------------------------------
//  GLUT reshape callback
// ---------------------------------------------------------------
static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
}

// ---------------------------------------------------------------
//  OpenGL one-time init
// ---------------------------------------------------------------
static void initGL()
{
    GLenum err = glewInit();
    if (err != GLEW_OK)
        exit(1);

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.022f, 0.055f, 0.085f, 1.0f);   // dark teal space
}

// ---------------------------------------------------------------
//  main
// ---------------------------------------------------------------
int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Assignment 1 - Space Shooter Arcade Scene");

    initGL();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);

    printf("Controls: O=Ortho, P=Perspective, ESC=Exit\n");
    printf("Click the OpenGL window first, then press keys.\n");

    glutMainLoop();
    return 0;
}