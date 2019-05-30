/**
 * @file draw_circle.cpp
 * @author Nguyen Quang <nguyenquang.emailbox@gmail.com>
 * @brief The circle drawing algorithms in computer graphics.
 * @since 0.0.1
 * 
 * @copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
 * 
 */

#include <iostream>
#include <algorithm>
#include <math.h>
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
 * @param[in] ms The time in minisecond.
 * @since 0.0.1
 */
void timer(int ms);

/**
 * @brief Draw a circle using the square root method.
 * 
 * @param[in] x_c The x-coordiante of the circle centre.
 * @param[in] y_c The y-coordiante of the circle centre.
 * @param[in] r The radius of the circle.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_circle_sqrt(int x_c, int y_c, int r, std::vector<Point2i>& vertices);

/**
 * @brief Draw a circle using the polar enhancement method.
 * 
 * @param[in] x_c The x-coordiante of the circle centre.
 * @param[in] y_c The y-coordiante of the circle centre.
 * @param[in] r The radius of the circle.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_circle_polar_enhancement(int x_c, int y_c, int r, std::vector<Point2i>& vertices);

/**
 * @brief Draw a circle using the midpoint algorithm.
 * 
 * @param[in] x_c The x-coordiante of the circle centre.
 * @param[in] y_c The y-coordiante of the circle centre.
 * @param[in] r The radius of the circle.
 * @param[out] vertices The list of pixels need to be drawn.
 * @since 0.0.1
 */
void draw_circle_midpoint(int x_c, int y_c, int r, std::vector<Point2i>& vertices);

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
    glutCreateWindow("draw_circle");
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
    int x_c = 130;
    int y_c = 125;
    int r = 120;
    int iterations = 1000;

    // Draw cirles using the square root method
    std::vector<Point2i> vertices_sqrt;
    for (int i = 0; i < iterations; i++) {
        draw_circle_sqrt(x_c, y_c, r, vertices_sqrt);
    }

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_sqrt.size(); i++) {
            glVertex2d(vertices_sqrt[i].x, vertices_sqrt[i].y);
        }
    }
    glEnd();

    // Draw cirles using the polar enhancement method
    std::vector<Point2i> vertices_polar_enhancement;
    for (int i = 0; i < iterations; i++) {
        draw_circle_polar_enhancement(x_c, y_c, r, vertices_polar_enhancement);
    }

    // Drift the circle 300 pixels right to see all algorithms at the same time
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_polar_enhancement.size(); i++) {
            glVertex2d(vertices_polar_enhancement[i].x + 300, vertices_polar_enhancement[i].y);
        }
    }
    glEnd();

    // Draw cirles using the midpoint algorithm
    std::vector<Point2i> vertices_midpoint;
    for (int i = 0; i < iterations; i++) {
        draw_circle_midpoint(x_c, y_c, r, vertices_midpoint);
    }

    // Drift the circle 150 pixels right and 220 pixel up to see all algorithms at the same time
    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_POINTS);
    {
        for (int i = 0; i < vertices_midpoint.size(); i++) {
            glVertex2d(vertices_midpoint[i].x + 150, vertices_midpoint[i].y + 220);
        }
    }
    glEnd();

    glFlush();
}

void timer(int ms) {
    glutPostRedisplay();
    glutTimerFunc(ms, timer, ms);
}

void draw_circle_sqrt(int x_c, int y_c, int r, std::vector<Point2i>& vertices) {
    vertices.clear();
    for (int x = x_c - r; x < x_c + r; x++) {
        int d_x = x_c - x;
        int y = std::round(sqrt(r * r - d_x * d_x));
        vertices.push_back(Point2i(x, y_c + y));
        vertices.push_back(Point2i(x, y_c - y));
    }
}

void draw_circle_polar_enhancement(int x_c, int y_c, int r, std::vector<Point2i>& vertices) {
    vertices.clear();
    float d_theta = 1.0f / r;
    float two_pi = 2 * M_PI;
    for (float theta = 0; theta < two_pi; theta += d_theta) {
        int x = x_c + std::round(r * cos(theta));
        int y = y_c + std::round(r * sin(theta));
        vertices.push_back(Point2i(x, y));
    }
}

void draw_circle_midpoint(int x_c, int y_c, int r, std::vector<Point2i>& vertices) {
    vertices.clear();
    float p = 5 / 4 - r;
    int x = 0;
    int y = r;
    vertices.push_back(Point2i(x_c + x, y_c + y));
    vertices.push_back(Point2i(x_c + y, y_c + x));
    vertices.push_back(Point2i(x_c + y, y_c - x));
    vertices.push_back(Point2i(x_c + x, y_c - y));
    vertices.push_back(Point2i(x_c - x, y_c - y));
    vertices.push_back(Point2i(x_c - y, y_c - x));
    vertices.push_back(Point2i(x_c - y, y_c + x));
    vertices.push_back(Point2i(x_c - x, y_c + y));

    while (x < y) {
        if (p < 0) {
            p = p + 2 * x + 3;
        } else {
            p = p + 2 * x - 2 * y + 5;
            y = y - 1;
        }
        x = x + 1;
        vertices.push_back(Point2i(x_c + x, y_c + y));
        vertices.push_back(Point2i(x_c + y, y_c + x));
        vertices.push_back(Point2i(x_c + y, y_c - x));
        vertices.push_back(Point2i(x_c + x, y_c - y));
        vertices.push_back(Point2i(x_c - x, y_c - y));
        vertices.push_back(Point2i(x_c - y, y_c - x));
        vertices.push_back(Point2i(x_c - y, y_c + x));
        vertices.push_back(Point2i(x_c - x, y_c + y));
    }
}
