from PIL import Image, ImageDraw

def koch_curve(start, end, order):
    if order == 0:
        return [start, end]
    else:
        # Calculate the points of the Koch curve
        dx = (end[0] - start[0]) / 3
        dy = (end[1] - start[1]) / 3

        p1 = start
        p2 = (p1[0] + dx, p1[1] + dy)
        p3 = (p2[0] + dx * 0.5 - dy * 0.866, p2[1] + dy * 0.5 + dx * 0.866)
        p4 = (p1[0] + dx * 2, p1[1] + dy * 2)
        p5 = end

        # Recursively calculate points for each segment of the curve
        points = []
        points.extend(koch_curve(p1, p2, order - 1))
        points.extend(koch_curve(p2, p3, order - 1))
        points.extend(koch_curve(p3, p4, order - 1))
        points.extend(koch_curve(p4, p5, order - 1))

        return points

width = 2400
height = 1200
img = Image.new("RGB", (width, height), "white")
draw = ImageDraw.Draw(img)

start_point = (0, 50)
end_point = (width, 50)
order = 8

points = koch_curve(start_point, end_point, order)
for i in range(len(points)-1):
    draw.line([points[i],points[i+1]], fill="black", width=1)

img = img.transpose(Image.FLIP_TOP_BOTTOM)
img.save("koch_enyem.png")
img.show()