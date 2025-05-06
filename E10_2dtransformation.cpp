#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

struct Point {
    float x, y;
};

Point triangle[3] = { {100, 100}, {200, 100}, {150, 200} };
Point transformed[3];

int windowWidth = 600, windowHeight = 600;

// Copy original to transformed
void resetTransformation() {
    for (int i = 0; i < 3; i++) {
        transformed[i] = triangle[i];
    }
}

void drawTriangle(Point tri[3], float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++) {
        glVertex2f(tri[i].x, tri[i].y);
    }
    glEnd();
}

void scale(float sx, float sy) {
    for (int i = 0; i < 3; i++) {
        transformed[i].x *= sx;
        transformed[i].y *= sy;
    }
}

void rotate(float angleDeg, float rx, float ry) {
    float angleRad = angleDeg * M_PI / 180.0;
    float cosA = cos(angleRad);
    float sinA = sin(angleRad);

    for (int i = 0; i < 3; i++) {
        float x = transformed[i].x - rx;
        float y = transformed[i].y - ry;

        float xNew = x * cosA - y * sinA;
        float yNew = x * sinA + y * cosA;

        transformed[i].x = xNew + rx;
        transformed[i].y = yNew + ry;
    }
}

void reflect(char axis) {
    float cx = windowWidth / 2.0;
    float cy = windowHeight / 2.0;

    for (int i = 0; i < 3; i++) {
        if (axis == 'x') {
            transformed[i].y = 2 * cy - transformed[i].y;
        } else if (axis == 'y') {
            transformed[i].x = 2 * cx - transformed[i].x;
        } else if (axis == 'o') {
            transformed[i].x = 2 * cx - transformed[i].x;
            transformed[i].y = 2 * cy - transformed[i].y;
        }
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Original Triangle in Blue
    drawTriangle(triangle, 0, 0, 1);

    // Transformed Triangle in Red
    drawTriangle(transformed, 1, 0, 0);

    glFlush();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 's':
            scale(1.5, 1.5);
            break;
        case 'r':
            rotate(45, 150, 150); // rotate 45 deg about point (150, 150)
            break;
        case 'x':
            reflect('x');
            break;
        case 'y':
            reflect('y');
            break;
        case 'o':
            reflect('o');
            break;
        case 'e':
            resetTransformation();
            break;
    }
    glutPostRedisplay();
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
    resetTransformation();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("2D Transformations");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
