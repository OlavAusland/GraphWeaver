import numpy as np
import graph_weaver as gw


def graph_weaver_init():
    pass


def graph_weaver_update():
    x = np.arange(0, 1000, 0.1)
    y = np.cos(x*1) * -1
    gw.set_color("SinCurve", 0.0, 1.0, 1.0, 1.0)
    gw.set_color("Test1", 1.0, 0.0, 1.0, 1.0)
    gw.draw_line("SinCurve", x.tolist(), y.tolist())
