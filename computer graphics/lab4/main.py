import time
import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button

WINDOW_SIZE = 10

global r_slider, x1_slider, y1_slider, x2_slider, y2_slider, button
x1_slider = {}
y1_slider = {}
x2_slider = {}
y2_slider = {}
button = {}
r_slider = {}

f, ax = plt.subplots(1, 4, figsize=(WINDOW_SIZE, WINDOW_SIZE))
f.subplots_adjust(top = 0.9, right = 0.95, left = 0.05)

def draw_sliders_buttons():
    pos = ax[3].get_position()
    x1_slider[3] = Slider(f.add_axes([pos.x0, pos.y0 * 1.8, pos.width * 0.9, pos.height * 0.05]), 'x1', 0, 350, valinit=50, valstep=1)
    y1_slider[3] = Slider(f.add_axes([pos.x0, pos.y0 * 1.4, pos.width * 0.9, pos.height * 0.05]), 'y1', 0, 350, valinit=50, valstep=1)
    r_slider[3] = Slider(f.add_axes([pos.x0, pos.y0 * 1.0, pos.width * 0.9, pos.height * 0.05]), 'r', 0, 150, valinit=20, valstep=1)
    button[3] = Button(f.add_axes([pos.x0, pos.y0 * 0.2, pos.width * 0.3, pos.height * 0.05]), 'submit') 
    for i in range(3):
        pos = ax[i].get_position()
        x1_slider[i] = Slider(f.add_axes([pos.x0, pos.y0 * 1.8, pos.width * 0.9, pos.height * 0.05]), 'x1', 0, 500, valinit=100, valstep=1)
        y1_slider[i] = Slider(f.add_axes([pos.x0, pos.y0 * 1.4, pos.width * 0.9, pos.height * 0.05]), 'y1', 0, 500, valinit=0, valstep=1)
        x2_slider[i] = Slider(f.add_axes([pos.x0, pos.y0 * 1.0, pos.width * 0.9, pos.height * 0.05]), 'x2', 0, 500, valinit=0, valstep=1)
        y2_slider[i] = Slider(f.add_axes([pos.x0, pos.y0 * 0.6, pos.width * 0.9, pos.height * 0.05]), 'y2', 0, 500, valinit=100, valstep=1)
        button[i] = Button(f.add_axes([pos.x0, pos.y0 * 0.2, pos.width * 0.3, pos.height * 0.05]), 'submit') 


def lets_swap(x1, y1, x2, y2):
    if x1 > x2 or y1 > y2:
        x1, x2 = x2, x1
        y1, y2 = y2, y1
    return x1, y1, x2, y2


def step_by_step(x1, y1, x2, y2):
    x1, y1, x2, y2 = lets_swap(x1, y1, x2, y2)
    k = (y2 - y1)
    if (x2 - x1) != 0:
        k = (y2 - y1)/(x2 - x1)
    
    b = y2 - k * x2
    dx = abs(x2 - x1)/(max(abs(x2 - x1), abs(y2 - y1) * 2))
    if (x2 > x1):
        dx = dx
    else:
        dx = -dx
    
    img = np.zeros((max(y1, y2) + 1, max(x1, x2) + 1))
    x = x1
    y = k * x + b
    begin = time.time()
    while x < x2:
        img[int(y), int(x)] = 1
        y = k * x + b
        x += dx
    end = time.time()
        
    draw_graph(img, 0, 'step by step algo', max(x1, x2, y1, y2), min(x1, x2, y1, y2), end - begin)


def digital_diff(x1, y1, x2, y2):
    x1, y1, x2, y2 = lets_swap(x1, y1, x2, y2)
    start_x = x1
    start_y = y1
    dx = x2 - x1
    dy = y2 - y1

    steps = max(dx, dy)

    x_inc = dx / steps
    y_inc = dy / steps
    img = np.zeros((max(y1, y2) + 1, max(x1, x2) + 1))
    begin = time.time()
    for i in range(int(steps)):
        img[int(y1), int(x1)] = 1
        x1 += x_inc
        y1 += y_inc
    end = time.time()

    draw_graph(img, 1, 'dda algo', max(start_x, x2, start_y, y2), min(start_x, x2, start_y, y2), end - begin)


def bresenham_line(x1, y1, x2, y2):
    x1, y1, x2, y2 = lets_swap(x1, y1, x2, y2)
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)
    x_sign = 1 if x1 < x2 else -1
    y_sign = 1 if y1 < y2 else -1
    err = dx - dy
    x = x1
    y = y1

    img = np.zeros((max(y1, y2) + 1, max(x1, x2) + 1))
    begin = time.time()
    while x < x2 or y < y2:
        img[int(y), int(x)] = 1
        e2 = err * 2
        if e2 > -dy:
            err -= dy
            x += x_sign
        if e2 < dx:
            err += dx
            y += y_sign
    end = time.time()
    
    draw_graph(img, 2, 'bresenhem line', max(x1, x2, y1, y2), min(x1, x2, y1, y2), end - begin)


def bresenham_circle(xc, yc, r):
    x = 0
    y = r
    err = 3 - 2 * r
    img = np.zeros((2 * r + 1 + yc, 2 * r + 1 + xc))
    begin = time.time()
    if xc < r:
        xc = r
    if yc < r:
        yc = r
    while x <= y:
        img[yc + y][xc + x] = 1
        img[yc + y][xc - x] = 1
        img[yc - y][xc + x] = 1
        img[yc - y][xc - x] = 1
        img[yc + x][xc + y] = 1
        img[yc + x][xc - y] = 1
        img[yc - x][xc + y] = 1
        img[yc - x][xc - y] = 1
        if err > 0:
            err += 4 * (x - y) + 10
            y -= 1
        else:
            err += 4 * x + 6
        x += 1
    end = time.time()

    draw_graph(img, 3, "bresenham circle", max(xc + r, yc + r), min(xc - r, yc - r), end - begin)


def draw_graph(img, column, title, maxx, minn, time):
    ax[column].cla()
    ax[column].set_xlim(minn - 10, maxx + 10)
    ax[column].set_ylim(minn - 10, maxx + 10)
    ax[column].set_title(title)
    ax[column].set_xlabel("x points")
    ax[column].set_ylabel("y points")
    ax[column].tick_params(axis='x')
    ax[column].tick_params(axis='y')
    ax[column].grid(True)
    ax[column].text(0.5, 1.2, f"time: {time:.10f} s", fontsize=12, ha='center', va='center', transform=ax[column].transAxes)
    filtered_img = cv2.GaussianBlur(img, ksize=(3, 3), sigmaX =0, sigmaY=0)
    ax[column].imshow(filtered_img,  cmap='binary')
    plt.draw()


def update_sbs(event):
    step_by_step(x1_slider[0].val, y1_slider[0].val, x2_slider[0].val, y2_slider[0].val)


def update_dda(event):
    digital_diff(x1_slider[1].val, y1_slider[1].val, x2_slider[1].val, y2_slider[1].val)


def update_line(event):
    bresenham_line(x1_slider[2].val, y1_slider[2].val, x2_slider[2].val, y2_slider[2].val)


def update_circle(event):
    bresenham_circle(x1_slider[3].val, y1_slider[3].val, r_slider[3].val)


draw_sliders_buttons()

step_by_step(x1_slider[0].val, y1_slider[0].val, x2_slider[0].val, y2_slider[0].val)
digital_diff(x1_slider[1].val, y1_slider[1].val, x2_slider[1].val, y2_slider[1].val)
bresenham_line(x1_slider[2].val, y1_slider[2].val, x2_slider[2].val, y2_slider[2].val)
bresenham_circle(x1_slider[3].val, y1_slider[3].val, r_slider[3].val)


button[0].on_clicked(update_sbs)
button[1].on_clicked(update_dda)
button[2].on_clicked(update_line)
button[3].on_clicked(update_circle)


plt.show()
