#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

int recursionDepth = 4;

void drawKoch(float x1, float y1, float x2, float y2, int depth) {
    if (depth == 0) {
        glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glEnd();
        glFlush();
        return;
    }

    float dx = (x2 - x1) / 3;
    float dy = (y2 - y1) / 3;

    float x3 = x1 + dx;
    float y3 = y1 + dy;

    float x5 = x2 - dx;
    float y5 = y2 - dy;

    float x4 = 0.5 * (x1 + x2) - sqrt(3.0) * (y1 - y2) / 6;
    float y4 = 0.5 * (y1 + y2) - sqrt(3.0) * (x2 - x1) / 6;

    drawKoch(x1, y1, x3, y3, depth - 1);
    drawKoch(x3, y3, x4, y4, depth - 1);
    drawKoch(x4, y4, x5, y5, depth - 1);
    drawKoch(x5, y5, x2, y2, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f);
    drawKoch(-200, 0, 200, 0, recursionDepth);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(-300, 300, -300, 300);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Koch Curve Fractal");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
