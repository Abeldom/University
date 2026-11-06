from PIL import Image, ImageDraw

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
image.save("5_vicsek.png")
