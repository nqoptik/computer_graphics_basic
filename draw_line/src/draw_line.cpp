/**
 * @file draw_line.cpp
 * @author Nguyen Quang <nguyenquang.emailbox@gmail.com>
 * @brief The line drawing algorithms in computer graphics.
 * @since 0.0.1
 * 
 * @copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
 * 
 */

#include <iostream>
#include <algorithm>
#include <vector>
#include <sys/time.h>
#include <GL/glut.h>

/**
 * @brief A struct to store 2D integer points.
 * 
 * @since 0.0.1
 * 
 */
struct Point2i {
    int x;
    int y;

    /**
     * @brief Construct a new Point 2i object.
     * 
     * @param[in] x The x-coordinate.
     * @param[in] y The y-coordinate.
     * @since 0.0.1
     */
    Point2i(int x = 0, int y = 0) {
        this->x = x;
        this->y = y;
    }
};

/**
 * @brief Initialize opengl state.
 * 
 * @since 0.0.1
 * 
 */
void initial();

/**
 * @brief The openGL display function.
 * 
 * @since 0.0.1
 * 
 */
void display();

/**
 * @brief The timer callback function.
 * 
 * @param[i] n The time in minisecond.
 * @since 0.0.1
 */
void timer(int ms);

/**
 * @brief Draw a line using equation directly.
 * 
 * @param[in] x_0 The x-coordiante of the first point.
 * @param[in] y_0 The y-coordiante of the first point.
 * @param[in] x_1 The x-coordiante of the second point.
 * @param[in] y_1 The y-coordiante of the second point.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_line_equation(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices);

/**
 * @brief Draw a line using DDA algorithm.
 * 
 * @param[in] x_0 The x-coordiante of the first point.
 * @param[in] y_0 The y-coordiante of the first point.
 * @param[in] x_1 The x-coordiante of the second point.
 * @param[in] y_1 The y-coordiante of the second point.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_line_dda(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices);

/**
 * @brief Draw a line using Bresenham algorithm.
 * 
 * @param[in] x_0 The x-coordiante of the first point.
 * @param[in] y_0 The y-coordiante of the first point.
 * @param[in] x_1 The x-coordiante of the second point.
 * @param[in] y_1 The y-coordiante of the second point.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_line_bresenhame(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices);

/**
 * @brief The main function.
 * 
 * @param[in] argc The argument count.
 * @param[in] argv The argument vector.
 * @return The status value.
 * @since 0.0.1
 */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("draw_line");
    initial();
    timer(5);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

void initial() {
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 640, 0, 480);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    int x_0 = 460;
    int y_0 = 320;
    int x_1 = 10;
    int y_1 = 190;
    int iterations = 1000;
    struct timeval tv[6];

    // Draw lines using equation directly
    std::vector<Point2i> vertices_equation, vertices_equation_t;
    gettimeofday(&tv[0], NULL);
    for (int i = 0; i < iterations; i++) {
        draw_line_equation(x_0, y_0, x_1, y_1, vertices_equation);
        draw_line_equation(y_0, x_0, y_1, x_1, vertices_equation_t);
    }
    gettimeofday(&tv[1], NULL);

    // Drift the lines 5 pixels right and 5 pixel up to see all algorithms at the same time
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_equation.size(); i++) {
            glVertex2d(vertices_equation[i].x + 5, vertices_equation[i].y + 5);
        }
        for (int i = 0; i < vertices_equation_t.size(); i++) {
            glVertex2d(vertices_equation_t[i].x + 5, vertices_equation_t[i].y + 5);
        }
    }
    glEnd();

    // Draw lines using DDA algorithm
    std::vector<Point2i> vertices_dda, vertices_dda_t;
    gettimeofday(&tv[2], NULL);
    for (int i = 0; i < iterations; i++) {
        draw_line_dda(x_0, y_0, x_1, y_1, vertices_dda);
        draw_line_dda(y_0, x_0, y_1, x_1, vertices_dda_t);
    }
    gettimeofday(&tv[3], NULL);

    // Drift the lines 10 pixels right and 10 pixel up to see all algorithms at the same time
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_dda.size(); i++) {
            glVertex2d(vertices_dda[i].x + 10, vertices_dda[i].y + 10);
        }
        for (int i = 0; i < vertices_dda_t.size(); i++) {
            glVertex2d(vertices_dda_t[i].x + 10, vertices_dda_t[i].y + 10);
        }
    }
    glEnd();

    // Draw lines using Bresenham algorithm
    std::vector<Point2i> vertices_bresenham, vertices_bresenham_t;
    gettimeofday(&tv[4], NULL);
    for (int i = 0; i < iterations; i++) {
        draw_line_bresenhame(x_0, y_0, x_1, y_1, vertices_bresenham);
        draw_line_bresenhame(y_0, x_0, y_1, x_1, vertices_bresenham_t);
    }
    gettimeofday(&tv[5], NULL);

    // Drift the lines 15 pixels right and 15 pixel up to see all algorithms at the same time
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_bresenham.size(); i++) {
            glVertex2d(vertices_bresenham[i].x + 15, vertices_bresenham[i].y + 15);
        }
        for (int i = 0; i < vertices_bresenham_t.size(); i++) {
            glVertex2d(vertices_bresenham_t[i].x + 15, vertices_bresenham_t[i].y + 15);
        }
    }
    glEnd();

    int time[3];
    time[0] = (tv[1].tv_sec - tv[0].tv_sec) * 1e6 + (tv[1].tv_usec - tv[0].tv_usec);
    time[1] = (tv[3].tv_sec - tv[2].tv_sec) * 1e6 + (tv[3].tv_usec - tv[2].tv_usec);
    time[2] = (tv[5].tv_sec - tv[4].tv_sec) * 1e6 + (tv[5].tv_usec - tv[4].tv_usec);

    std::cout << "Time for equation->dda->bresenham: " << time[0] << "->" << time[1] << "->" << time[2] << std::endl;

    glFlush();
}

void timer(int ms) {
    glutPostRedisplay();
    glutTimerFunc(ms, timer, ms);
}

void draw_line_equation(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices) {
    vertices.clear();
    if ((x_0 == x_1) and (y_0 == y_1)) {
        vertices.push_back(Point2i(x_0, y_0));
    } else {
        int d_x = x_1 - x_0;
        int d_y = y_1 - y_0;
        if (abs(d_x) >= abs(d_y)) {
            if (x_0 > x_1) {
                // swap x_0 and x_1
                int tmp = x_0;
                x_0 = x_1;
                x_1 = tmp;

                // swap y_0 and y_1
                tmp = y_0;
                y_0 = y_1;
                y_1 = tmp;
            }
            float m = (float)d_y / d_x;
            float b = y_0 - m * x_0;
            for (int x = x_0; x <= x_1; x++) {
                int y = std::round(m * x + b);
                vertices.push_back(Point2i(x, y));
            }
        } else {
            if (y_0 > y_1) {
                // swap x_0 and x_1
                int tmp = x_0;
                x_0 = x_1;
                x_1 = tmp;

                // swap y_0 and y_1
                tmp = y_0;
                y_0 = y_1;
                y_1 = tmp;
            }
            float m = (float)d_x / d_y;
            float b = x_0 - m * y_0;
            for (int y = y_0; y <= y_1; y++) {
                int x = std::round(m * y + b);
                vertices.push_back(Point2i(x, y));
            }
        }
    }
}

void draw_line_dda(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices) {
    vertices.clear();
    if ((x_0 == x_1) && (y_0 == y_1)) {
        vertices.push_back(Point2i(x_0, y_0));
    } else {
        int d_x = x_1 - x_0;
        int d_y = y_1 - y_0;
        if (abs(d_x) >= abs(d_y)) {
            if (x_0 > x_1) {
                // swap x_0 and x_1
                int tmp = x_0;
                x_0 = x_1;
                x_1 = tmp;

                // swap y_0 and y_1
                tmp = y_0;
                y_0 = y_1;
                y_1 = tmp;
            }

            float m = (float)d_y / d_x;
            float y = y_0;
            for (int x = x_0; x <= x_1; x++) {
                int round_y = std::round(y);
                vertices.push_back(Point2i(x, round_y));
                y = y + m;
            }
        } else {
            if (y_0 > y_1) {
                // swap x_0 and x_1
                int tmp = x_0;
                x_0 = x_1;
                x_1 = tmp;

                // swap y_0 and y_1
                tmp = y_0;
                y_0 = y_1;
                y_1 = tmp;
            }

            float m = (float)d_x / d_y;
            float x = x_0;
            for (int y = y_0; y <= y_1; y++) {
                int round_x = std::round(x);
                vertices.push_back(Point2i(round_x, y));
                x = x + m;
            }
        }
    }
}

void draw_line_bresenhame(int x_0, int y_0, int x_1, int y_1, std::vector<Point2i>& vertices) {
    vertices.clear();
    if (abs(x_1 - x_0) > abs(y_1 - y_0)) {
        if (x_0 > x_1) {
            // swap x_0 and x_1
            int tmp = x_0;
            x_0 = x_1;
            x_1 = tmp;

            // swap y_0 and y_1
            tmp = y_0;
            y_0 = y_1;
            y_1 = tmp;
        }

        int d_x = x_1 - x_0;
        int d_y = y_1 - y_0;
        if (d_y > 0) {
            int p = 2 * d_y - d_x;
            int y = y_0;
            for (int x = x_0; x <= x_1; x++) {
                vertices.push_back(Point2i(x, y));
                if (p > 0) {
                    y = y + 1;
                    p = p - 2 * d_x;
                }
                p = p + 2 * d_y;
            }
        } else {
            int p = 2 * d_y + d_x;
            int y = y_0;
            for (int x = x_0; x <= x_1; x++) {
                vertices.push_back(Point2i(x, y));
                if (p < 0) {
                    y = y - 1;
                    p = p + 2 * d_x;
                }
                p = p + 2 * d_y;
            }
        }
    } else {
        if (y_0 > y_1) {
            // swap x_0 and x_1
            int tmp = x_0;
            x_0 = x_1;
            x_1 = tmp;

            // swap y_0 and y_1
            tmp = y_0;
            y_0 = y_1;
            y_1 = tmp;
        }

        int d_x = x_1 - x_0;
        int d_y = y_1 - y_0;
        if (d_x > 0) {
            int p = 2 * d_x - d_y;
            int x = x_0;
            for (int y = y_0; y <= y_1; y++) {
                vertices.push_back(Point2i(x, y));
                if (p > 0) {
                    x = x + 1;
                    p = p - 2 * d_y;
                }
                p = p + 2 * d_x;
            }
        } else {
            int p = 2 * d_x + d_y;
            int x = x_0;
            for (int y = y_0; y <= y_1; y++) {
                vertices.push_back(Point2i(x, y));
                if (p < 0) {
                    x = x - 1;
                    p = p + 2 * d_y;
                }
                p = p + 2 * d_x;
            }
        }
    }
}
