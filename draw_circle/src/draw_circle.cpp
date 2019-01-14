#include <stdio.h>

#ifdef __linux__
#include <GL/glut.h>
#else
#include <glut.h>
#endif

void importingData();
void initial();
void circleMidPoint(void);

int xC, yC;
float R, p;

int main(int argc, char** argv) {
    importingData();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1352, 688);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("draw_circle");
    initial();
    glutDisplayFunc(circleMidPoint);
    glutMainLoop();
    return 1;
}

void importingData() {
    printf("Enter center point's coordinate.\n");
    printf("xC = ");
    if (scanf("%d", &xC) < 1) {
        printf("Failed to enter xC.\n");
    }
    printf("yC = ");
    if (scanf("%d", &yC) < 1) {
        printf("Failed to enter yC.\n");
    }
    printf("Enter radius R = ");
    if (scanf("%f", &R) < 1) {
        printf("Failed to enter R.\n");
    }
}

void initial() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-676.0, 676.0, -344.0, 344.0, -1.0, 1.0);
}

void circleMidPoint(void) {
    p = 5 / 4 - R;
    int x = 0;
    float y = R;
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_LINES);
    {
        glVertex2d(0, -344);
        glVertex2d(0, 344);
        glVertex2d(-676, 0);
        glVertex2d(676, 0);
    }
    glEnd();

    glPointSize(2.0);
    glColor3f(0.0, 0.0, 1.0);

    glBegin(GL_POINTS);
    {
        glVertex2d(xC, yC);
    }
    glEnd();

    glBegin(GL_POINTS);
    {
        glVertex2d(xC + x, yC + y);
        glVertex2d(xC + y, yC + x);
        glVertex2d(xC + y, yC - x);
        glVertex2d(xC + x, yC - y);
        glVertex2d(xC - x, yC - y);
        glVertex2d(xC - y, yC - x);
        glVertex2d(xC - y, yC + x);
        glVertex2d(xC - x, yC + y);
    }
    glEnd();

    while (x < y) {
        if (p < 0) {
            p = p + 2 * x + 3;
        } else {
            p = p + 2 * x - 2 * y + 5;
            y = y - 1;
        }

        x = x + 1;

        glBegin(GL_POINTS);
        {
            glVertex2d(xC + x, yC + y);
            glVertex2d(xC + y, yC + x);
            glVertex2d(xC + y, yC - x);
            glVertex2d(xC + x, yC - y);
            glVertex2d(xC - x, yC - y);
            glVertex2d(xC - y, yC - x);
            glVertex2d(xC - y, yC + x);
            glVertex2d(xC - x, yC + y);
        }
        glEnd();
    }

    glFlush();
}
