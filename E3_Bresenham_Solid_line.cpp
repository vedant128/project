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

void drawSolidBresenham(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x2 >= x1 ? 1 : -1;
    int sy = y2 >= y1 ? 1 : -1;
    bool isSteep = dy > dx;
    if (isSteep) {
        swap(x1, y1);
        swap(x2, y2);
        swap(dx, dy);
        swap(sx, sy);
    }

    int d = 2 * dy - dx;
    int x = x1, y = y1;

    glBegin(GL_POINTS);
    for (int i = 0; i <= dx; i++) {
        if (isSteep)
            glVertex2i(y, x);
        else
            glVertex2i(x, y);

        if (d > 0) {
            y += sy;
            d -= 2 * dx;
        }
        d += 2 * dy;
        x += sx;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawSolidBresenham(-100, -50, 100, 50);
    drawSolidBresenham(-100, 50, 100, -50);
    drawSolidBresenham(0, -200, 0, 200);
    drawSolidBresenham(-200, 0, 200, 0);
    drawSolidBresenham(-50, -200, 50, 200);
    drawSolidBresenham(200, 100, -200, -100);
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
    glutCreateWindow("Bresenham Solid Line - 4 Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
