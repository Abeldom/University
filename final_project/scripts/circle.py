from PIL import Image, ImageDraw
from pathlib import Path

project_dir = Path(__file__).resolve().parents[1]
image_dir = project_dir / "images"

width = 1500
height = 1500
img = Image.new("RGB", (width, height), "white")

center = (750, 750)  # Example center coordinates
radius = 700 

draw = ImageDraw.Draw(img)
draw.ellipse((center[0] - radius, center[1] - radius, center[0] + radius, center[1] + radius), outline='black')
img.save(image_dir / "circle_line.png")
img.show()