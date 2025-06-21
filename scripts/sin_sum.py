import graph_weaver as gw
import numpy as np


def graph_weaver_update():
    x = np.arange(-10, 10, 0.01)
    y_1 = np.sin(x**1.2)
    y_2 = np.cos(x + 0.75)

    gw.set_color("Y_1", 1.0, 0.0, 1.0, 1.0)
    gw.draw_line("Y_1", x.tolist(), y_1.tolist())
    gw.draw_line("Y_2", x.tolist(), y_2.tolist())
    gw.set_color("Y_3", 0.0, 0.0, 1.0, 1.0)
    gw.draw_line("Y_3", x.tolist(), (y_1 + y_2).tolist())
