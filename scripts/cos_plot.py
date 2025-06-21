import numpy as np
import graph_weaver as gw


def graph_weaver_init():
    pass


def graph_weaver_update():
    gw.set_color("Test1", 1.0, 1.0, 1.0, 1.0)

    x = np.arange(0, 100, 0.1)
    y = np.cos(x)
    gw.draw_line("Test1", x.tolist(), y.tolist())
