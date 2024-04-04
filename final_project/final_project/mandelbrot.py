import numpy as np
import matplotlib.pyplot as plt

def mandelbrot(c, max_iter):
    z = 0
    n = 0
    while abs(z) <= 2 and n < max_iter:
        z = z**2 + c
        n += 1
    return n

def mandelbrot_set(xmin, xmax, ymin, ymax, width, height, max_iter):
    x = np.linspace(xmin, xmax, width)
    y = np.linspace(ymin, ymax, height)
    mandelbrot_image = np.zeros((height, width))

    for i in range(height):
        for j in range(width):
            mandelbrot_image[i, j] = mandelbrot(x[j] + 1j * y[i], max_iter)

    return mandelbrot_image

def display_mandelbrot(xmin, xmax, ymin, ymax, width, height, max_iter):
    mandelbrot_image = mandelbrot_set(xmin, xmax, ymin, ymax, width, height, max_iter)
    plt.imshow(mandelbrot_image, extent=(xmin, xmax, ymin, ymax))
    plt.colorbar()
    plt.title("Fractal Mandelbrot")
    plt.xlabel("Re(c)")
    plt.ylabel("Im(c)")
    plt.show()

# Parametrii pentru setul Mandelbrot
xmin, xmax = -2.0, 1.0
ymin, ymax = -1.5, 1.5
width, height = 1000, 1000
max_iter = 100

# Afișare fractal Mandelbrot
display_mandelbrot(xmin, xmax, ymin, ymax, width, height, max_iter)
