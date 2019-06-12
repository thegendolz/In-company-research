import alphathree
import matplotlib.pyplot as plt
from PIL import Image

Parent = []

def initialize():
    img = Image.open('image_1.jpg')

    alreadyAdded = set()
    newImg = []
    alpha = 1

    width, height = img.size;

    ## Initialization of the alpha tree itself
    initializationAlphatree()

    img.show()

def initializationAlphatree(at, NodeMMG, img, p, q, dir):
    node, size = len(NodeMMG)

    for p in(p <= img.size-1):
        create_set(p)
        for q

def create_set(p):
    Parent[p] = -1
    return Parent[p]

def find_root(p , par_p):
    par_p = Parent[p]
    if par_p >= 0:
        par_p = find_root(par_p)
        return par_p
    else:
        return p

def criterion(p, q, a):
    d = compute_dissimilarity(p, q)
    if(d <= a):
        return True
    else:
        return False

def compute_dissimilarity(p, q):
    return abs(p-q)

def union(p, q, a):
    r = find_root(q)
    if r != p:
        if criterion(p, r, a):
            Parent[r] = p
            return True
        else:
            return False

initialize()
