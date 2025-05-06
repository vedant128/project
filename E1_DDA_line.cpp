#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

void drawDDALine(int x1, int y1, int x2, int y2) {
    float dx = x2 - x1;
    float dy = y2 - y1;
    float steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xInc = dx / steps;
    float yInc = dy / steps;
    float x = x1;
    float y = y1;
    glBegin(GL_POINTS);
    for (int i = 0; i <= steps; i++) {
        glVertex2i(round(x), round(y));
        x += xInc;
        y += yInc;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawDDALine(-100, -50, 100, 50);
    drawDDALine(-100, 50, 100, -50);
    drawDDALine(0, -200, 0, 200);
    drawDDALine(-200, 0, 200, 0);
    drawDDALine(-50, -200, 50, 200);
    drawDDALine(200, 100, -200, -100);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA Line Drawing Algorithm - 4 Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
