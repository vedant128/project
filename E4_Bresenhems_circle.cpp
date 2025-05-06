#include <GL/glut.h>
#include <cmath>
using namespace std;

void drawAxes() {
    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

void plotCirclePoints(int xc, int yc, int x, int y) {
    glVertex2i(xc + x, yc + y);
    glVertex2i(xc - x, yc + y);
    glVertex2i(xc + x, yc - y);
    glVertex2i(xc - x, yc - y);
    glVertex2i(xc + y, yc + x);
    glVertex2i(xc - y, yc + x);
    glVertex2i(xc + y, yc - x);
    glVertex2i(xc - y, yc - x);
}

void drawBresenhamCircle(int xc, int yc, int r) {
    int x = 0, y = r;
    int d = 3 - 2 * r;
    glBegin(GL_POINTS);
    while (x <= y) {
        plotCirclePoints(xc, yc, x, y);
        if (d < 0)
            d += 4 * x + 6;
        else {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
    drawBresenhamCircle(150, 150, 100);
    drawBresenhamCircle(-150, 150, 100);
    drawBresenhamCircle(-150, -150, 100);
    drawBresenhamCircle(150, -150, 100);
    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    gluOrtho2D(-500, 500, -500, 500);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Circle - All Quadrants");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
