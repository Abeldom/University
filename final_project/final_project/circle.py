from PIL import Image, ImageDraw

width = 1500
height = 1500
img = Image.new("RGB", (width, height), "white")

center = (750, 750)  # Example center coordinates
radius = 700 

draw = ImageDraw.Draw(img)
draw.ellipse((center[0] - radius, center[1] - radius, center[0] + radius, center[1] + radius), outline='black')
img.save("circle_line.png")
img.show()