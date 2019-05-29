#!/usr/bin/env python3

"""!@file draw_circle.py
@author Nguyen Quang <nguyenquang.emailbox@gmail.com>
@brief The circle drawing algorithms in computer graphics.
@since 0.0.1
@copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
"""

import time
import math
from pyglet.gl import *

window = pyglet.window.Window()


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
            p = p + 2*x + 3
        else:
            p = p + 2*x - 2*y + 5
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

    x_c = 300
    y_c = 200
    r = 150
    iterations = 1000

    # Draw circles using the midpoint algorithm
    vertices_midpoint = []
    begin = time.time()
    for i in range(iterations):
        vertices_midpoint = draw_circle_midpoint(x_c, y_c, r)
    end = time.time()
    print("Time to draw " + str(iterations) + " circles using the midpoint algorithm: " + str(end - begin))

    circle_midpoint = pyglet.graphics.vertex_list(int(len(vertices_midpoint)/2), ('v2f', vertices_midpoint))
    glColor3f(1, 0, 0)
    circle_midpoint.draw(GL_POINTS)


if __name__ == "__main__":
    pyglet.app.run()
