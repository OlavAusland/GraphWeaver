import numpy as np
import graph_weaver as gw

# Global time variable to track rotation
t = 0.0

x = np.ndarray
y = np.ndarray


def graph_weaver_init():
    global x, y

    angles = np.linspace(0, 2 * np.pi, 20)
    x = np.cos(angles)
    y = np.sin(angles)
    gw.set_color("Circle", 1.0, 1.0, 0.2, 1)
    # gw.draw_points("Initial Circle", x.tolist(), y.tolist())


def graph_weaver_update():
    global t
    t += 0.001  # Controls rotation speed


    # Original circle points

    # Rotation matrix around Z-axis by angle t
    cos_t = np.cos(t)
    sin_t = np.sin(t)
    x_rot = x * cos_t - y * sin_t
    y_rot = x * sin_t + y * cos_t

    gw.draw_points("Circle", x_rot.tolist(), y_rot.tolist())

