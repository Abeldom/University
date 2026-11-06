from PIL import Image, ImageDraw

image_path = "vicsek.png"
image = Image.open(image_path)
image = image.convert("RGB")

for i in range(5):
        for j in range(5):
            r, g, b = image.getpixel((i, j))


r, g, b = image.getpixel((0, 0))
print(r,g,b)