#!/usr/bin/env python3

"""!@file draw_line.py
@author Nguyen Quang <nguyenquang.emailbox@gmail.com>
@brief The line drawing algorithms in computer graphics.
@since 0.0.1
@copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
"""

import time
import math
from pyglet.gl import *

window = pyglet.window.Window()


def draw_line_equation(x_0, y_0, x_1, y_1):
    """!@brief Draw a line using equation directly.
    @since 0.0.1
    """

    vertices = []
    if x_0 == x_1 and y_0 == y_1:
        vertices += [x_0, y_0]
    else:
        d_x = x_1 - x_0
        d_y = y_1 - y_0
        if abs(d_x) >= abs(d_y):
            if x_0 > x_1:
                x_0, x_1 = x_1, x_0
                y_0, y_1 = y_1, y_0

            m = float(d_y)/d_x
            b = y_0 - m*x_0
            for x in range(x_0, x_1 + 1):
                vertices += [x, int(math.floor(m*x + b + 0.5))]
        else:
            if y_0 > y_1:
                x_0, x_1 = x_1, x_0
                y_0, y_1 = y_1, y_0

            m = float(d_x)/d_y
            b = x_0 - m*y_0
            for y in range(y_0, y_1 + 1):
                vertices += [int(math.floor(m*y + b + 0.5)), y]

    return vertices


def draw_line_dda(x_0, y_0, x_1, y_1):
    """!@brief Draw a line using DDA algorithm.
    @since 0.0.1
    """

    vertices = []
    if x_0 == x_1 and y_0 == y_1:
        vertices += [x_0, y_0]
    else:
        d_x = x_1 - x_0
        d_y = y_1 - y_0
        if abs(d_x) >= abs(d_y):
            if x_0 > x_1:
                x_0, x_1 = x_1, x_0
                y_0, y_1 = y_1, y_0

            m = float(d_y)/d_x
            y = y_0
            for x in range(x_0, x_1 + 1):
                vertices += [x, int(math.floor(y + 0.5))]
                y = y + m
        else:
            if y_0 > y_1:
                x_0, x_1 = x_1, x_0
                y_0, y_1 = y_1, y_0

            m = float(d_x)/d_y
            x = x_0
            for y in range(y_0, y_1 + 1):
                vertices += [int(math.floor(x + 0.5)), y]
                x = x + m

    return vertices


def draw_line_bresenham(x_0, y_0, x_1, y_1):
    """!@brief Draw a line using Bresenham algorithm.
    @since 0.0.1
    """

    vertices = []
    if abs(x_1 - x_0) > abs(y_1 - y_0):
        if x_0 > x_1:
            x_0, x_1 = x_1, x_0
            y_0, y_1 = y_1, y_0

        d_x = x_1 - x_0
        d_y = y_1 - y_0
        if d_y > 0:
            p = 2*d_y - d_x
            y = y_0
            for x in range(x_0, x_1 + 1):
                vertices += [x, y]
                if p > 0:
                    y = y + 1
                    p = p - 2*d_x
                p = p + 2*d_y
        else:
            p = 2*d_y + d_x
            y = y_0
            for x in range(x_0, x_1 + 1):
                vertices += [x, y]
                if p < 0:
                    y = y - 1
                    p = p + 2*d_x
                p = p + 2*d_y
    else:
        if y_0 > y_1:
            x_0, x_1 = x_1, x_0
            y_0, y_1 = y_1, y_0

        d_x = x_1 - x_0
        d_y = y_1 - y_0
        if d_x > 0:
            p = 2*d_x - d_y
            x = x_0
            for y in range(y_0, y_1 + 1):
                vertices += [x, y]
                if p > 0:
                    x = x + 1
                    p = p - 2*d_y
                p = p + 2*d_x
        else:
            p = 2*d_x + d_y
            x = x_0
            for y in range(y_0, y_1 + 1):
                vertices += [x, y]
                if p < 0:
                    x = x - 1
                    p = p + 2*d_y
                p = p + 2*d_x

    return vertices


@window.event
def on_draw():
    glClear(pyglet.gl.GL_COLOR_BUFFER_BIT)

    x_0 = 460
    y_0 = 320
    x_1 = 10
    y_1 = 190
    iterations = 1000

    # Draw two lines using equation directly
    vertices_equation = []
    vertices_equation_t = []
    begin = time.time()
    for i in range(iterations):
        vertices_equation = draw_line_equation(x_0, y_0, x_1, y_1)
        vertices_equation_t = draw_line_equation(y_0, x_0, y_1, x_1)
    end = time.time()
    print("Time do draw " + str(iterations) + " lines using equation directly: " + str(end - begin))
    line_equation = pyglet.graphics.vertex_list(int(len(vertices_equation)/2), ('v2f', vertices_equation))
    line_equation_t = pyglet.graphics.vertex_list(int(len(vertices_equation_t)/2), ('v2f', vertices_equation_t))
    glColor3f(1, 0, 0)
    line_equation.draw(GL_POINTS)
    line_equation_t.draw(GL_POINTS)

    # Draw two lines using DDA algorithm
    vertices_dda = []
    vertices_dda_t = []
    begin = time.time()
    for i in range(iterations):
        vertices_dda = draw_line_dda(x_0, y_0, x_1, y_1)
        vertices_dda_t = draw_line_dda(y_0, x_0, y_1, x_1)
    end = time.time()
    print("Time do draw " + str(iterations) + " lines using dda algorithm: " + str(end - begin))
    line_dda = pyglet.graphics.vertex_list(int(len(vertices_dda)/2), ('v2f', vertices_dda))
    line_dda_t = pyglet.graphics.vertex_list(int(len(vertices_dda_t)/2), ('v2f', vertices_dda_t))
    glColor3f(0, 1, 0)
    line_dda.draw(GL_POINTS)
    line_dda_t.draw(GL_POINTS)

    # Draw two lines using Bresenham algorithm
    vertices_bresenham = []
    vertices_bresenham_t = []
    begin = time.time()
    for i in range(iterations):
        vertices_bresenham = draw_line_bresenham(x_0, y_0, x_1, y_1)
        vertices_bresenham_t = draw_line_bresenham(y_0, x_0, y_1, x_1)
    end = time.time()
    print("Time do draw " + str(iterations) + " lines using bresenham algorithm: " + str(end - begin))
    line_bresenham = pyglet.graphics.vertex_list(int(len(vertices_bresenham)/2), ('v2f', vertices_bresenham))
    line_bresenham_t = pyglet.graphics.vertex_list(int(len(vertices_bresenham_t)/2), ('v2f', vertices_bresenham_t))

    glColor3f(0, 0, 1)
    line_bresenham.draw(GL_POINTS)
    line_bresenham_t.draw(GL_POINTS)


if __name__ == "__main__":
    pyglet.app.run()
