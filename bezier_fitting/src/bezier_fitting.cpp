#include <stdio.h>
#include <math.h>

#ifdef __linux__
#include <GL/glut.h>
#else
#include <glut.h>
#endif

void ImportingData();
void ComputePoints();
void Initial();
void Bezier(void);
void Mouse(int, int, int, int);
void WritingData();

char FileName[] = "bezier_fitting.data";
float Mouse1[2], Mouse2[2];
int n, Smooth = 2000, Check = 0;
float X[20][20], Y[20][20];
float x[4][27], y[4][27];
float t;

int main(int argc, char **argv) {
    ImportingData();
    ComputePoints();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1368, 696);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("bezier_fitting");
    Initial();
    glutDisplayFunc(Bezier);
    glutMouseFunc(Mouse);
    glutMainLoop();
    return 1;
}

void ImportingData() {
    FILE *p;
    p = fopen("bezier_fitting.data", "r");
    if (p == NULL) {
        printf("Error");
    } else {
        fscanf(p, "%d\n", &n);
        for (int i = 0; i < n; i++) {
            fscanf(p, "%f", &X[0][i]);
            fscanf(p, "%f\n", &Y[0][i]);
        }
        fclose(p);
    }

    Mouse1[0] = 1000;
    Mouse1[1] = 1000;
    Mouse2[0] = 1000;
    Mouse2[1] = 1000;
}

void ComputePoints() {
    if (n <= 4) {
        for (int i = 0; i < n; i++) {
            x[0][i] = X[0][i];
            y[0][i] = Y[0][i];
        }
    } else {
        for (int i = 0; i < 3; i++) {
            x[0][i] = X[0][i];
            y[0][i] = Y[0][i];
        }

        if (n % 2 == 0) {
            for (int i = 3; i < n - 3 + n / 2; i++) {
                if (i % 3 == 0) {
                    x[0][i] = (X[0][2 * i / 3] + X[0][2 * i / 3 + 1]) / 2;
                    y[0][i] = (Y[0][2 * i / 3] + Y[0][2 * i / 3 + 1]) / 2;
                } else {
                    x[0][i] = X[0][i - i / 3];
                    y[0][i] = Y[0][i - i / 3];
                }
                x[0][n - 3 + n / 2] = X[0][n - 1];
                y[0][n - 3 + n / 2] = Y[0][n - 1];
            }
        } else {
            for (int i = 3; i < n - 2 + n / 2; i++) {
                if (i % 3 == 0) {
                    x[0][i] = (X[0][2 * i / 3] + X[0][2 * i / 3 + 1]) / 2;
                    y[0][i] = (Y[0][2 * i / 3] + Y[0][2 * i / 3 + 1]) / 2;
                } else {
                    x[0][i] = X[0][i - i / 3];
                    y[0][i] = Y[0][i - i / 3];
                }
                x[0][n - 2 + n / 2] = x[0][n - 3 + n / 2];
                x[0][n - 1 + n / 2] = X[0][n - 1];
                y[0][n - 2 + n / 2] = y[0][n - 3 + n / 2];
                y[0][n - 1 + n / 2] = Y[0][n - 1];
            }
        }
    }
}

void Initial() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(1.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-684.0, 684.0, -348.0, 348.0, -1.0, 1.0);
}

void Bezier(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0);

    for (int i = 0; i < n - 1; i++) {
        glBegin(GL_LINES);
        {
            glVertex2d(X[0][i], Y[0][i]);
            glVertex2d(X[0][i + 1], Y[0][i + 1]);
        }
        glEnd();
    }

    glPointSize(10.0);
    for (int i = 0; i < n; i++) {
        glBegin(GL_POINTS);
        {
            glVertex2d(X[0][i], Y[0][i]);
        }
        glEnd();
    }

    glPointSize(3.0);
    for (t = 1; t < Smooth; t++) {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < n - i; j++) {
                X[i][j] = X[i - 1][j] + (X[i - 1][j + 1] - X[i - 1][j]) * t / Smooth;
                Y[i][j] = Y[i - 1][j] + (Y[i - 1][j + 1] - Y[i - 1][j]) * t / Smooth;
            }
        }

        glColor3f(1.0, 0.0, 1.0);
        glBegin(GL_POINTS);
        {
            glVertex2d(X[n - 1][0], Y[n - 1][0]);
        }
        glEnd();

        glColor3f(0.0, 0.0, 1.0);
        if (n <= 4) {
            for (int i = 1; i < n; i++) {
                for (int j = 0; j < n - i; j++) {
                    x[i][j] = x[i - 1][j] + (x[i - 1][j + 1] - x[i - 1][j]) * t / Smooth;
                    y[i][j] = y[i - 1][j] + (y[i - 1][j + 1] - y[i - 1][j]) * t / Smooth;
                }
            }

            glBegin(GL_POINTS);
            {
                glVertex2d(x[n - 1][0], y[n - 1][0]);
            }
            glEnd();
        } else {
            for (int i = 1; i < 4; i++) {
                for (int j = 0; j <= n - 2 + n / 2; j++) {
                    x[i][j] = x[i - 1][j] + (x[i - 1][j + 1] - x[i - 1][j]) * t / Smooth;
                    y[i][j] = y[i - 1][j] + (y[i - 1][j + 1] - y[i - 1][j]) * t / Smooth;
                }
            }

            glBegin(GL_POINTS);
            {
                for (int i = 0; i < (n - 1) / 2; i++) {
                    glVertex2d(x[3][3 * i], y[3][3 * i]);
                }
            }
            glEnd();
        }
    }
    glFlush();
}

void Mouse(int button, int state, int x, int y) {
    if (button == 0) {
        if (x > 1367)
            x = 1367;
        if (x < 0)
            x = 0;
        if (y < 0)
            y = 0;
        if (y > 695)
            y = 695;
        if (state == 0) {
            Mouse1[0] = x - 683;
            Mouse1[1] = 347 - y;
        } else {
            Mouse2[0] = x - 683;
            Mouse2[1] = 347 - y;
            Check = 1;
        }

        if (((Mouse1[0] != Mouse2[0]) | (Mouse1[1] != Mouse2[1])) & (Check == 1)) {
            for (int i = 0; i < n; i++) {
                if ((fabs(Mouse1[0] - X[0][i]) < 10) & (fabs(Mouse1[1] - Y[0][i]) < 10)) {
                    X[0][i] = Mouse2[0];
                    Y[0][i] = Mouse2[1];
                    WritingData();
                }
            }
            ComputePoints();
            glutPostRedisplay();

            Check = 0;
            Mouse1[0] = 1000;
            Mouse1[1] = 1000;
            Mouse2[0] = 1000;
            Mouse2[1] = 1000;
        }
    }
}

void WritingData() {
    FILE *p;
    p = fopen("bezier_fitting.data", "w");
    if (p == NULL) {
        printf("Error");
    } else {
        fprintf(p, "%d\n", n);
        for (int i = 0; i < n; i++) {
            fprintf(p, "%6.0f %6.0f \n", X[0][i], Y[0][i]);
        }
        fclose(p);
    }
}
