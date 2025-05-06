#include <GL/glut.h>
#include <iostream>
using namespace std;

float wxmin = 100, wymin = 100, wxmax = 300, wymax = 300;
float x_start, y_start, x_end, y_end;
bool lineDefined = false;
bool clipped = false;

const int INSIDE = 0;
const int LEFT = 1;
const int RIGHT = 2;
const int BOTTOM = 4;
const int TOP = 8;

int computeOutCode(float x, float y) {
    int code = INSIDE;
    if (x < wxmin) code |= LEFT;
    else if (x > wxmax) code |= RIGHT;
    if (y < wymin) code |= BOTTOM;
    else if (y > wymax) code |= TOP;
    return code;
}

bool cohenSutherlandClip() {
    int outcode0 = computeOutCode(x_start, y_start);
    int outcode1 = computeOutCode(x_end, y_end);
    bool accept = false;

    while (true) {
        if (!(outcode0 | outcode1)) {
            accept = true;
            break;
        } else if (outcode0 & outcode1) {
            break;
        } else {
            float x, y;
            int outcodeOut = outcode0 ? outcode0 : outcode1;

            if (outcodeOut & TOP) {
                x = x_start + (x_end - x_start) * (wymax - y_start) / (y_end - y_start);
                y = wymax;
            } else if (outcodeOut & BOTTOM) {
                x = x_start + (x_end - x_start) * (wymin - y_start) / (y_end - y_start);
                y = wymin;
            } else if (outcodeOut & RIGHT) {
                y = y_start + (y_end - y_start) * (wxmax - x_start) / (x_end - x_start);
                x = wxmax;
            } else {
                y = y_start + (y_end - y_start) * (wxmin - x_start) / (x_end - x_start);
                x = wxmin;
            }

            if (outcodeOut == outcode0) {
                x_start = x;
                y_start = y;
                outcode0 = computeOutCode(x_start, y_start);
            } else {
                x_end = x;
                y_end = y;
                outcode1 = computeOutCode(x_end, y_end);
            }
        }
    }
    return accept;
}

void drawLine() {
    glColor3f(0, 0, 1);
    glBegin(GL_LINES);
    glVertex2f(x_start, y_start);
    glVertex2f(x_end, y_end);
    glEnd();
    glFlush();
}

void drawWindow() {
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(wxmin, wymin);
    glVertex2f(wxmax, wymin);
    glVertex2f(wxmax, wymax);
    glVertex2f(wxmin, wymax);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawWindow();
    if (lineDefined) {
        if (clipped) {
            if (cohenSutherlandClip()) {
                drawLine();
            }
        } else {
            drawLine();
        }
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 600 - y;
        if (!lineDefined) {
            x_start = x;
            y_start = y;
            lineDefined = true;
        } else {
            x_end = x;
            y_end = y;
            clipped = false;
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int, int) {
    if (key == 'c' || key == 'C') {
        clipped = true;
        glutPostRedisplay();
    } else if (key == 'r' || key == 'R') {
        lineDefined = false;
        clipped = false;
        glutPostRedisplay();
    }
}

void init() {
    glClearColor(1, 1, 1, 1);
    gluOrtho2D(0, 600, 0, 600);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Cohen-Sutherland Line Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
