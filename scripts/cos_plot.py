import numpy as np
import graph_weaver as gw

def graph_weaver_update():
    x = np.arange(0, 1_000, 0.1)
    y = np.cos(x*1)

    gw.draw_line(x.tolist(), y.tolist())
