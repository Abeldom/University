from PIL import Image, ImageDraw
from pathlib import Path

project_dir = Path(__file__).resolve().parents[1]
image_dir = project_dir / "images"

def draw_square(x, y, size):
    half_size = size / 2
    draw.rectangle([x - half_size, y - half_size, x + half_size, y + half_size], fill="black")

def generate_vicsek(x, y, size, depth):

    if depth == 0:
        draw_square(x,y,size)
    else:
        new_size = size / 3
        generate_vicsek(x - new_size, y - new_size, new_size, depth - 1)
        generate_vicsek(x - new_size, y + new_size, new_size, depth - 1)

        generate_vicsek(x, y, new_size, depth - 1)

        generate_vicsek(x + new_size, y - new_size, new_size, depth - 1)
        generate_vicsek(x + new_size, y + new_size, new_size, depth - 1)

depth=7
image_size=6000

image = Image.new("RGB", (image_size,image_size), "white")
draw = ImageDraw.Draw(image)
generate_vicsek(image_size/2,image_size/2, image_size, depth)

# Example: Generate Vicsek fractal image with size 100 and depth 3
image.show()
# Save the image
image.save(image_dir / "5_vicsek.png")
