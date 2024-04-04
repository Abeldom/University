from PIL import Image
import math
import matplotlib.pyplot as plt
import numpy as np

image_path = "koch_enyem.png" 
output_path = "modified_example.png"

image = Image.open(image_path)

image = image.convert("RGB")

width, height = image.size
black_counter=0
white_counter=0
x_coord=[]
y_coord=[]

def fekete(image, x,y, hossz):
    # print("idaig")
    for i in range(hossz):
        for j in range(hossz):
            r, g, b = image.getpixel((x+i, y+j))
            if (r+g+b)/3<30: #ha eleg sotet, akkor az egesz negyzetet besotetiti
                for i in range(hossz):
                    for j in range(hossz):
                        image.putpixel((x+i, y+j), (0,0,0))
                return 1
                
    return 0

def closest_line_to_points(x_coord,y_coord):
    A = np.vstack([x_coord, np.ones(len(x_coord))]).T
    m, b = np.linalg.lstsq(A, y_coord, rcond=None)[0]
    
    return m, b

#---------------------------------------------------

for n in range(24,3,-4): #finomitani, skalazni
    
    for x in range(0,width-n,n): #vegig menni a racspontokon
        for y in range(0,height-n,n):
            if(fekete(image,x,y,n)): black_counter = black_counter+1 #hogyha van metszes fekete resszel
            else: white_counter = white_counter+1

    x_coord.append(math.log10(n/2400))
    y_coord.append(math.log10(black_counter))
    print(n,black_counter, white_counter, white_counter/black_counter)
    black_counter=0
    white_counter=0

    image.save(output_path)
    image = Image.open(image_path)

#megkeresi a legjobb kozelitest az egyenesekre
m, b = closest_line_to_points(x_coord,y_coord)
print(-m)

x_min = min(x_coord)
x_max = max(x_coord)

plt.scatter(x_coord, y_coord, color='blue', label='Points')
plt.plot([x_min, x_max], [m * x_min + b, m * x_max + b], color='red', label='Closest Line')
plt.xlabel('log(s)')
plt.ylabel('log(N(s))')
plt.title('')

plt.grid(True)
plt.legend()
plt.show()

# for x in range(width):
#     for y in range(height):
#         # Get the RGB values of the pixel at position (x, y)
#         r, g, b = image.getpixel((x, y))
        
#         # Example: Invert the colors of the image
#         new_r = 255 - r
#         new_g = 255 - g
#         new_b = 255 - b

#         # Set the new RGB values for the pixel at position (x, y)
#         image.putpixel((x, y), (new_r, new_g, new_b))
