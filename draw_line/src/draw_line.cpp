#include <stdio.h>

#ifdef __linux__
#include <GL/glut.h>
#else
#include <glut.h>
#endif

void importingData();
void initial();
void lineDDA(void);
void lineMidPoint(void);

int xA, yA, xB, yB, check;

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    importingData();
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1352, 688);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("draw_line");
    initial();

    if (check == 1) {
        glutDisplayFunc(lineDDA);
    } else {
        if (check == 2) {
            glutDisplayFunc(lineMidPoint);
        }
    }
    glutMainLoop();
    return 1;
}

void importingData() {
    printf("Enter A, B's coordinates:\n");
    printf("xA = ");
    scanf("%d", &xA);
    printf("yA = ");
    scanf("%d", &yA);
    printf("xB = ");
    scanf("%d", &xB);
    printf("yB = ");
    scanf("%d", &yB);

    if (xA > xB) {
        int xC, yC;
        xC = xA;
        yC = yA;
        xA = xB;
        yA = yB;
        xB = xC;
        yB = yC;
    }
    printf("Pick one of these following algorithms to draw the line:\n");
    printf("1. DDA algorithm.\n");
    printf("2. Midpoint algorithm.\n");
    scanf("%d", &check);
}

void initial() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-676.0, 676.0, -344.0, 344.0, -1.0, 1.0);
}

void lineDDA(void) {
    float Dy = yB - yA;
    float Dx = xB - xA;
    float Px = xA;
    float Py = yA;
    float m;

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

    if (Dx == 0) {
        for (int i = 0; i <= yB - yA; i++) {
            glBegin(GL_POINTS);
            {
                glVertex2d(Px, Py + i);
            }
            glEnd();
        }
    } else {
        m = Dy / Dx;

        glBegin(GL_POINTS);
        {
            if ((m < 1) && (m > -1)) {
                for (int i = 0; i <= xB - xA; i++) {
                    Py = Py + m;
                    glVertex2d(xA + i, Py);
                }
            } else {
                if (yA < yB) {
                    for (int i = 0; i <= yB - yA; i++) {
                        Px = Px + 1 / m;
                        glVertex2d(Px, yA + i);
                    }
                } else {
                    for (int i = 0; i <= yA - yB; i++) {
                        Px = Px - 1 / m;
                        glVertex2d(Px, yA - i);
                    }
                }
            }
        }
        glEnd();
    }

    glFlush();
}

void lineMidPoint(void) {
    float Dy = yB - yA;
    float Dx = xB - xA;
    float x = xA;
    float y = yA;
    float m, p;

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

    if (Dx == 0) {
        for (int i = 0; i <= yB - yA; i++) {
            glBegin(GL_POINTS);
            {
                glVertex2d(x, y + i);
            }
            glEnd();
        }
    } else {
        m = Dy / Dx;

        if ((m <= 1) && (m >= 0)) {
            p = 2 * Dy - Dx;

            glBegin(GL_POINTS);
            {
                glVertex2d(x, y);
            }
            glEnd();

            while (x < xB) {
                if (p >= 0) {
                    y = y + 1;
                    p = p + 2 * Dy - 2 * Dx;
                } else {
                    p = p + 2 * Dy;
                }

                x = x + 1;

                glBegin(GL_POINTS);
                {
                    glVertex2d(x, y);
                }
                glEnd();
            }
        } else {
            if ((m < 0) && (m >= -1)) {
                p = 2 * Dy - Dx;

                glBegin(GL_POINTS);
                {
                    glVertex2d(x, y);
                }
                glEnd();

                while (x < xB) {
                    if (p <= 0) {
                        y = y - 1;
                        p = p + 2 * Dy + 2 * Dx;
                    } else {
                        p = p + 2 * Dy;
                    }

                    x = x + 1;

                    glBegin(GL_POINTS);
                    {
                        glVertex2d(x, y);
                    }
                    glEnd();
                }
            } else {
                if (m < -1) {
                    p = 2 * Dx + Dy;
                    x = xB;
                    y = yB;

                    glBegin(GL_POINTS);
                    {
                        glVertex2d(x, y);
                    }
                    glEnd();

                    while (y < yA) {
                        if (p >= 0) {
                            x = x - 1;
                            p = p + 2 * Dx + 2 * Dy;
                        } else {
                            p = p + 2 * Dx;
                        }

                        y = y + 1;

                        glBegin(GL_POINTS);
                        {
                            glVertex2d(x, y);
                        }
                        glEnd();
                    }
                } else {
                    p = 2 * Dx - Dy;

                    glBegin(GL_POINTS);
                    {
                        glVertex2d(x, y);
                    }
                    glEnd();

                    while (y < yB) {
                        if (p >= 0) {
                            x = x + 1;
                            p = p + 2 * Dx - 2 * Dy;
                        } else {
                            p = p + 2 * Dx;
                        }

                        y = y + 1;

                        glBegin(GL_POINTS);
                        {
                            glVertex2d(x, y);
                        }
                        glEnd();
                    }
                }
            }
        }
    }

    glFlush();
}
