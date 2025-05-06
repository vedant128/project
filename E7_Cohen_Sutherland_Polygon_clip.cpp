#include <GL/glut.h>
#include <vector>
using namespace std;

struct Point {
    float x, y;
};

vector<Point> polygon;
bool clipped = false;

float wxmin = 100, wymin = 100, wxmax = 300, wymax = 300;

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

bool cohenSutherlandClip(float& x0, float& y0, float& x1, float& y1) {
    int outcode0 = computeOutCode(x0, y0);
    int outcode1 = computeOutCode(x1, y1);
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
                x = x0 + (x1 - x0) * (wymax - y0) / (y1 - y0);
                y = wymax;
            } else if (outcodeOut & BOTTOM) {
                x = x0 + (x1 - x0) * (wymin - y0) / (y1 - y0);
                y = wymin;
            } else if (outcodeOut & RIGHT) {
                y = y0 + (y1 - y0) * (wxmax - x0) / (x1 - x0);
                x = wxmax;
            } else {
                y = y0 + (y1 - y0) * (wxmin - x0) / (x1 - x0);
                x = wxmin;
            }

            if (outcodeOut == outcode0) {
                x0 = x;
                y0 = y;
                outcode0 = computeOutCode(x0, y0);
            } else {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            }
        }
    }
    return accept;
}

void drawPolygon(const vector<Point>& pts) {
    glBegin(GL_LINE_LOOP);
    for (const auto& p : pts)
        glVertex2f(p.x, p.y);
    glEnd();
}

void drawClippedPolygon() {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < polygon.size(); ++i) {
        float x0 = polygon[i].x;
        float y0 = polygon[i].y;
        float x1 = polygon[(i + 1) % polygon.size()].x;
        float y1 = polygon[(i + 1) % polygon.size()].y;
        if (cohenSutherlandClip(x0, y0, x1, y1)) {
            glVertex2f(x0, y0);
            glVertex2f(x1, y1);
        }
    }
    glEnd();
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
    if (!polygon.empty()) {
        glColor3f(0, 0, 1);
        if (!clipped)
            drawPolygon(polygon);
        else {
            glColor3f(0, 0.7, 0);
            drawClippedPolygon();
        }
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && !clipped) {
        y = 600 - y;
        polygon.push_back({(float)x, (float)y});
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'c' || key == 'C') {
        clipped = true;
        glutPostRedisplay();
    } else if (key == 'r' || key == 'R') {
        polygon.clear();
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
    glutCreateWindow("Cohen-Sutherland Polygon Clipping");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
