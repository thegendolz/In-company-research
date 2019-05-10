import alphathree
import matplotlib.pyplot as plt
from PIL import Image

def initialize():
    img = Image.open('driehoekig.pgm')
    
    alphaThree = alphathree.AlphaThree(10)

    img.show()


initialize()
