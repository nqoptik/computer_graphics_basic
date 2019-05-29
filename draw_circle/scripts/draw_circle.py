#!/usr/bin/env python3

"""!@file draw_circle.py
@author Nguyen Quang <nguyenquang.emailbox@gmail.com>
@brief The Circle drawing algorithms in computer graphics.
@since 0.0.1
@copyright Copyright (c) 2015, Nguyen Quang, all rights reserved.
"""

import time
import math
from pyglet.gl import *

window = pyglet.window.Window()


def draw_circle_midpoint(x, y, r):
    """!@brief Draw a circle using midpoint algorithm.
    @param[in] x The x-coordiante of the circle centre.
    @param[in] y The y-coordiante of the circle centre.
    @param[in] r The radius of the circle.
    @since 0.0.1
    """

    vertices = []
    p = float(5)/4 - r
    x_ = 0
    y_ = r

    vertices += [x + x_, y + y_]
    vertices += [x + y_, y + x_]
    vertices += [x + y_, y - x_]
    vertices += [x + x_, y - y_]
    vertices += [x - x_, y - y_]
    vertices += [x - y_, y - x_]
    vertices += [x - y_, y + x_]
    vertices += [x - x_, y + y_]

    while x_ < y_:
        if p < 0:
            p = p + 2*x_ + 3
        else:
            p = p + 2*x_ - 2*y_ + 5
            y_ = y_ - 1

        x_ = x_ + 1
        vertices += [x + x_, y + y_]
        vertices += [x + y_, y + x_]
        vertices += [x + y_, y - x_]
        vertices += [x + x_, y - y_]
        vertices += [x - x_, y - y_]
        vertices += [x - y_, y - x_]
        vertices += [x - y_, y + x_]
        vertices += [x - x_, y + y_]

    return vertices


@window.event
def on_draw():
    glClear(pyglet.gl.GL_COLOR_BUFFER_BIT)

    x = 300
    y = 200
    r = 150
    iterations = 1000

    # Draw two lines using equation directly
    vertices_midpoint = []
    begin = time.time()
    for i in range(iterations):
        vertices_midpoint = draw_circle_midpoint(x, y, r)
    end = time.time()
    print("Time do draw " + str(iterations) + " circles using midpoint algorithm: " + str(end - begin))

    circle_midpoint = pyglet.graphics.vertex_list(int(len(vertices_midpoint)/2), ('v2f', vertices_midpoint))
    glColor3f(1, 0, 0)
    circle_midpoint.draw(GL_POINTS)


if __name__ == "__main__":
    pyglet.app.run()
