import numpy as np
import graph_weaver as gw

x = np.ndarray
y = np.ndarray


def graph_weaver_init():
    global x, y
    x = np.arange(0, 100, 0.1)
    y = 1 * np.sin(x*2)
    gw.set_color(0.0, 1.0, 0.0, 1.0)
    gw.draw_line("Test123", x.tolist(), y.tolist())


def graph_weaver_update():
    pass
    # gw.draw_points(x.tolist(), y.tolist())
