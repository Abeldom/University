# - A fraktált nem iteráció szerint rajzolom meg, hanem a berajzolható körök
#   sugárhossza szerint: a túl kicsi köröket már nem rajzolom be.

import pygame
import math
import cmath
import time
from fractions import Fraction
from decimal import Decimal, getcontext
from pathlib import Path

getcontext().prec = 100

project_dir = Path(__file__).resolve().parents[1]
image_dir = project_dir / "images"

WIDTH, HEIGHT = 3000, 3000 # kép felbontása
EPSILON = 0.1              # pontosság mérésére
DISPLAY_TIME = 7           # másodpercben, megtekintési idő
CIRCLE_BORDER_WIDTH = 2    # körvonal vastagsága 

# A kör osztály definíciója
class Circle:
    def __init__(self, gorbulet, x, y):
        self.gorbulet = Fraction(Decimal(gorbulet))
        self.radius = Fraction(1, abs(self.gorbulet)) if self.gorbulet != 0 else float('inf')
        self.kozep = complex(Decimal(x),Decimal(y))

    def dist(self, other):
        return abs(self.kozep - other.kozep)

    def show(self, screen):
        pygame.draw.circle(screen, (0, 0, 0), (int(self.kozep.real), int(self.kozep.imag)), int(self.radius)+2, CIRCLE_BORDER_WIDTH)

# Néhány segítő függvény
def erinto(c1, c2):
    d = c1.dist(c2)
    r1, r2 = c1.radius, c2.radius
    a = abs(d - (r1 + r2)) < EPSILON
    b = abs(d - abs(r2 - r1)) < EPSILON
    return a or b

def validate(c4, c1, c2, c3, minden_kor):
    # túl kicsi köröket ne rajzoljunk
    # ez egyben leállási feltétel is
    if c4.radius < 5: 
        return False

    for other in minden_kor:
        d = c4.dist(other)
        radius_diff = abs(c4.radius - other.radius)
        if d < EPSILON and radius_diff < EPSILON:
            return False

    if not (erinto(c4, c1) and erinto(c4, c2) and erinto(c4, c3)):
        return False

    return True

def descartes(c1, c2, c3):
    k1, k2, k3 = c1.gorbulet, c2.gorbulet, c3.gorbulet
    sum_k = k1 + k2 + k3
    product_k = abs(k1 * k2 + k2 * k3 + k1 * k3)
    root = 2 * math.sqrt(product_k)
    return [sum_k + root, sum_k - root]

def complex_descartes(c1, c2, c3, k4):
    k1, k2, k3 = c1.gorbulet, c2.gorbulet, c3.gorbulet
    z1, z2, z3 = c1.kozep, c2.kozep, c3.kozep

    zk1, zk2, zk3 = z1 * k1, z2 * k2, z3 * k3
    sum_zk = zk1 + zk2 + zk3

    root =2* cmath.sqrt(zk1 * zk2 + zk2 * zk3 + zk1 * zk3)
    kozep1 = sum_zk + root
    kozep2 = sum_zk - root

    return [
        Circle(k4[0], kozep1.real / k4[0], kozep1.imag / k4[0]),
        Circle(k4[0], kozep2.real / k4[0], kozep2.imag / k4[0]),
        
        Circle(k4[1], kozep1.real / k4[1], kozep1.imag / k4[1]),
        Circle(k4[1], kozep2.real / k4[1], kozep2.imag / k4[1])
    ]

def kov_generacio(queue, minden_kor):
    next_queue = []
    for kor_harmas in queue:
        c1, c2, c3 = kor_harmas
        k4_ertekek = descartes(c1, c2, c3)
        uj_korok = complex_descartes(c1, c2, c3 ,k4_ertekek)

        for uj_kor in uj_korok:
            if validate(uj_kor, c1, c2, c3, minden_kor):
                minden_kor.append(uj_kor)
                next_queue.extend([[c1, c2, uj_kor], [c1, c3, uj_kor], [c2, c3, uj_kor]])
    return next_queue

pygame.init()
# Ha tul nagy felbontasu kepeket hozunk letre, akkor futattas
# kozben nem lehet jol megtekinteni a kepet, hanem csak lementes utan
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption('Circle Gasket')

# első három kör pozicionálása
c1 = Circle(-Decimal(1)/(Decimal(WIDTH)/2-100), WIDTH/2, HEIGHT/2)
c2 = Circle(Decimal(1)/(Decimal(WIDTH)/4-50), WIDTH/4+50, HEIGHT/2)
c3 = Circle(Decimal(1)/(Decimal(WIDTH)/4-50), WIDTH*3/4-50, HEIGHT/2)

minden_kor = [c1, c2, c3]
queue = [[c1, c2, c3]]

# Main
start_time = time.time()
running = True
screen.fill((255, 255, 255))
while running:
    for kor in minden_kor:
        kor.show(screen)

    db1 = len(minden_kor)
    queue = kov_generacio(queue, minden_kor)
    db2 = len(minden_kor)

    #ha nem hoztunk letre uj kort || lejart az ido, akkor megall a program
    if db1 == db2 and (time.time() - start_time) > DISPLAY_TIME:
        print('done')
        pygame.image.save(screen, str(image_dir / "apollonian_gasket.png"))
        running = False

    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    pygame.display.flip()

pygame.quit()
