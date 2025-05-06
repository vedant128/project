#include <GL/glut.h>
#include <cmath>

void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glPointSize(1.0);
}

// Compare two RGB colors with tolerance
bool isSameColor(float *a, float *b, float tol = 0.1f)
{
    return fabs(a[0] - b[0]) < tol &&
           fabs(a[1] - b[1]) < tol &&
           fabs(a[2] - b[2]) < tol;
}

// Recursive boundary fill
void boundaryFill(int x, int y, float *fill, float *boundary)
{
    float pixel[3];
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, pixel);

    if (!isSameColor(pixel, boundary) && !isSameColor(pixel, fill))
    {
        glColor3fv(fill);
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
        glFlush();

        boundaryFill(x + 1, y, fill, boundary);
        boundaryFill(x - 1, y, fill, boundary);
        boundaryFill(x, y + 1, fill, boundary);
        boundaryFill(x, y - 1, fill, boundary);
    }
}

// Mouse callback
void mouse(int btn, int state, int x, int y)
{
    if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        float boundary[] = {0.0f, 0.0f, 1.0f}; // Blue boundary
        float fill[] = {0.0f, 1.0f, 0.0f};     // Green fill
        boundaryFill(x, 480 - y, fill, boundary); // Convert to OpenGL y
    }
}

// Draw blue triangle
void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0f, 0.0f, 1.0f); // Blue

    glBegin(GL_LINE_LOOP);
    glVertex2i(150, 100);
    glVertex2i(300, 300);
    glVertex2i(450, 100);
    glEnd();
    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Boundary Fill - Triangle");
    init();
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
