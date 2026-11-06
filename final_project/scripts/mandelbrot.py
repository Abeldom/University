from PIL import Image
from pathlib import Path

project_dir = Path(__file__).resolve().parents[1]
image_dir = project_dir / "images"

def generate_mandelbrot(
    xmin: float,
    xmax: float,
    ymin: float,
    ymax: float,
    width: int,
    height: int,
    max_iterations: int,
) -> Image.Image:
    image = Image.new("RGB", (width, height), "white")
    pixels = image.load()

    for y in range(height):
        imaginary = ymin + (ymax - ymin) * y / (height - 1)
        for x in range(width):
            real = xmin + (xmax - xmin) * x / (width - 1)
            z_real = 0.0
            z_imaginary = 0.0
            iterations = 0
            while (
                z_real * z_real + z_imaginary * z_imaginary <= 4
                and iterations < max_iterations
            ):
                z_real, z_imaginary = (
                    z_real * z_real - z_imaginary * z_imaginary + real,
                    2 * z_real * z_imaginary + imaginary,
                )
                iterations += 1
            if iterations == max_iterations:
                pixels[x, y] = (0, 0, 0)

    return image


if __name__ == "__main__":
    image = generate_mandelbrot(
        xmin=-2.0,
        xmax=0.5,
        ymin=-1.0,
        ymax=1.0,
        width=1200,
        height=1200,
        max_iterations=80,
    )
    image.save(image_dir / "mandelbrot.png")
