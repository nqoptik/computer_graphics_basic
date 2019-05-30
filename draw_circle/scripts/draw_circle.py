#!/usr/bin/env python3

"""!@file draw_circle.py
@author Nguyen Quang <nguyenquang.emailbox@gmail.com>
@brief The circle drawing algorithms in computer graphics.
@since 0.0.1
@copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
"""

import time
import math
import numpy as np
from pyglet.gl import *

window = pyglet.window.Window()


def draw_circle_sqrt(x_c, y_c, r):
    """!@brief Draw a circle using the square root method.
    @param[in] x_c The x-coordiante of the circle centre.
    @param[in] y_c The y-coordiante of the circle centre.
    @param[in] r The radius of the circle.
    @since 0.0.1
    """

    vertices = []
    for x in range(x_c - r, x_c + r):
        d_x = x_c - x
        y = math.floor(math.sqrt(r * r - d_x * d_x) + 0.5)
        vertices += [x, y_c + y]
        vertices += [x, y_c - y]

    return vertices


def draw_circle_polar_enhancement(x_c, y_c, r):
    """!@brief Draw a circle using the polar enhancement method.
    @param[in] x_c The x-coordiante of the circle centre.
    @param[in] y_c The y-coordiante of the circle centre.
    @param[in] r The radius of the circle.
    @since 0.0.1
    """

    vertices = []
    d_theta = 1.0 / r
    two_pi = 2 * math.pi
    for theta in np.arange(0, two_pi, d_theta):
        x = x_c + math.floor(r * math.cos(theta) + 0.5)
        y = y_c + math.floor(r * math.sin(theta) + 0.5)
        vertices += [x, y]

    return vertices


def draw_circle_midpoint(x_c, y_c, r):
    """!@brief Draw a circle using the midpoint algorithm.
    @param[in] x_c The x-coordiante of the circle centre.
    @param[in] y_c The y-coordiante of the circle centre.
    @param[in] r The radius of the circle.
    @since 0.0.1
    """

    vertices = []
    p = float(5)/4 - r
    x = 0
    y = r

    vertices += [x_c + x, y_c + y]
    vertices += [x_c + y, y_c + x]
    vertices += [x_c + y, y_c - x]
    vertices += [x_c + x, y_c - y]
    vertices += [x_c - x, y_c - y]
    vertices += [x_c - y, y_c - x]
    vertices += [x_c - y, y_c + x]
    vertices += [x_c - x, y_c + y]

    while x < y:
        if p < 0:
            p = p + 2 * x + 3
        else:
            p = p + 2 * x - 2 * y + 5
            y = y - 1

        x = x + 1
        vertices += [x_c + x, y_c + y]
        vertices += [x_c + y, y_c + x]
        vertices += [x_c + y, y_c - x]
        vertices += [x_c + x, y_c - y]
        vertices += [x_c - x, y_c - y]
        vertices += [x_c - y, y_c - x]
        vertices += [x_c - y, y_c + x]
        vertices += [x_c - x, y_c + y]

    return vertices


@window.event
def on_draw():
    glClear(pyglet.gl.GL_COLOR_BUFFER_BIT)

    x_c = 130
    y_c = 125
    r = 120
    iterations = 1000

    # Draw circles using the square root method
    vertices_sqrt = []
    begin = time.time()
    for i in range(iterations):
        vertices_sqrt = draw_circle_sqrt(x_c, y_c, r)
    end = time.time()
    print("Time to draw " + str(iterations) + " circles using the square root method: " + str(end - begin))

    circle_sqrt = pyglet.graphics.vertex_list(int(len(vertices_sqrt)/2), ('v2f', vertices_sqrt))
    glColor3f(1, 0, 0)
    circle_sqrt.draw(GL_POINTS)

    # Draw circles using the polar enhancement method
    vertices_polar_enhancement = []
    begin = time.time()
    for i in range(iterations):
        vertices_polar_enhancement = draw_circle_polar_enhancement(x_c, y_c, r)
    end = time.time()
    print("Time to draw " + str(iterations) + " circles using the polar enhancement method: " + str(end - begin))

    # Drift the circle 300 pixels right to see all algorithms at the same time
    for i in range(len(vertices_polar_enhancement)):
        if i % 2 == 0:
            vertices_polar_enhancement[i] = vertices_polar_enhancement[i] + 300

    circle_polar_enhancement = pyglet.graphics.vertex_list(int(len(vertices_polar_enhancement)/2), ('v2f', vertices_polar_enhancement))
    glColor3f(0, 1, 0)
    circle_polar_enhancement.draw(GL_POINTS)

    # Draw circles using the midpoint algorithm
    vertices_midpoint = []
    begin = time.time()
    for i in range(iterations):
        vertices_midpoint = draw_circle_midpoint(x_c, y_c, r)
    end = time.time()
    print("Time to draw " + str(iterations) + " circles using the midpoint algorithm: " + str(end - begin))

    # Drift the circle 150 pixels right and 220 pixel up to see all algorithms at the same time
    for i in range(len(vertices_midpoint)):
        if i % 2 == 0:
            vertices_midpoint[i] = vertices_midpoint[i] + 150
        else:
            vertices_midpoint[i] = vertices_midpoint[i] + 220

    circle_midpoint = pyglet.graphics.vertex_list(int(len(vertices_midpoint)/2), ('v2f', vertices_midpoint))
    glColor3f(0, 0, 1)
    circle_midpoint.draw(GL_POINTS)


if __name__ == "__main__":
    pyglet.app.run()
