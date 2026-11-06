from PIL import Image, ImageDraw

def draw_square(x, y, size):
    half_size = size / 2
    draw.rectangle([x - half_size, y - half_size, x + half_size, y + half_size], fill="white")

def generate_vicsek(x, y, size, depth):
    if depth == 0:
        draw_square(x,y,size)
    else:
        new_size = size / 3
        generate_vicsek(x - size, y - size, new_size, depth - 1)
        generate_vicsek(x - size, y, new_size, depth - 1)
        generate_vicsek(x - size, y + size, new_size, depth - 1)

        generate_vicsek(x, y - size, new_size, depth - 1)
        draw_square(x,y,size)
        generate_vicsek(x, y + size, new_size, depth - 1)

        generate_vicsek(x + size, y - size, new_size, depth - 1)
        generate_vicsek(x + size, y, new_size, depth - 1)
        generate_vicsek(x + size, y + size, new_size, depth - 1)

    
    return image

depth=5
image_size=4000

image = Image.new("RGB", (image_size,image_size), "black")
draw = ImageDraw.Draw(image)
generate_vicsek(image_size/2,image_size/2, image_size/3, depth)

# Example: Generate Vicsek fractal image with size 100 and depth 3
image.show()
# Save the image
image.save("4_carpet_sajat.png")
