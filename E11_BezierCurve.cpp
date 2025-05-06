#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Point {
    float x, y;
};

// Control points for base Bézier curve
Point controlPoints[4] = {
    { -300, -100 },
    { -100,  300 },
    {  100, -300 },
    {  300,  100 }
};

int windowWidth = 800, windowHeight = 600;
int maxDepth = 4; // depth of recursion

// Linear interpolation
Point interpolate(Point a, Point b, float t) {
    return { a.x + (b.x - a.x) * t, a.y + (b.y - a.y) * t };
}

// Recursive Bézier using De Casteljau’s algorithm
void drawBezierRecursive(Point p0, Point p1, Point p2, Point p3, int depth) {
    if (depth <= 0) {
        // Draw as a straight line
        glBegin(GL_LINE_STRIP);
        glVertex2f(p0.x, p0.y);
        glVertex2f(p3.x, p3.y);
        glEnd();
        return;
    }

    // Subdivide the curve
    Point a = interpolate(p0, p1, 0.5);
    Point b = interpolate(p1, p2, 0.5);
    Point c = interpolate(p2, p3, 0.5);

    Point d = interpolate(a, b, 0.5);
    Point e = interpolate(b, c, 0.5);

    Point f = interpolate(d, e, 0.5);

    // Recursive calls
    drawBezierRecursive(p0, a, d, f, depth - 1);
    drawBezierRecursive(f, e, c, p3, depth - 1);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);
    drawBezierRecursive(controlPoints[0], controlPoints[1],
                        controlPoints[2], controlPoints[3], maxDepth);
    glFlush();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(-windowWidth / 2, windowWidth / 2, -windowHeight / 2, windowHeight / 2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Fractal Pattern using Bézier Curve");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
