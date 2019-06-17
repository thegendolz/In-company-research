import alphathree
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

Parent = []
img = [[0, 1, 5, 12, 1],
       [0, 1, 5, 12, 1],
       [0, 1, 5, 12, 1],
       [0, 1, 5, 12, 1],
       [0, 1, 3, 2, 1]] 
imgNodeId = [np.zeros((5,5))]
id = -1
width = 5
height = 5

def initialize():
    #img = Image.open('image_1.jpg')
    #width, height = 5;
    id = -1
    addEmptyLevel(0, width, height)


    ## Initialization of the alpha tree itself
    initializationAlphatree(width, height)

    #img.show()

def addEmptyLevel(level, width, height):
    #imgNodeId.append(np.zeros(width, height))

    for n in range(0, width):
        for m in range(0, height):
            imgNodeId[level][m, n] = -1
    print(imgNodeId[0])

def initializationAlphatree(width, height):
    rootNotReached = True;
    ACC = 0
    while rootNotReached: #As long as root is not reached, keep going with a lower alpha-cc
        for m in range(0, width):
            for n in range(0, height):
                lookForNeighbours(m, n, ACC, 4, width, height)

        rootNotReached = False
        print(imgNodeId[0])
        ACC+=1

def lookForNeighbours(m, n, alpha, CNNType, width, height):
    if(CNNType == 4):
        if m-1 > 0 and abs(img[m][n] - img[m - 1][n]) <= alpha: addToNode(alpha, m-1, n, m, n)
        if m + 1 < width and abs(img[m][n] - img[m + 1][n]) <= alpha: addToNode(alpha, m+1, n, m, n)
        if n+1 < height and abs(img[m][n] - img[m][n + 1]) <= alpha: addToNode(alpha, m, n+1, m, n)
        if n-1 > 0 and abs(img[m][n] - img[m][n - 1]) <= alpha: addToNode(alpha, m, n-1, m, n)

def addToNode(level, m, n, x, y):
    if imgNodeId[level][x, y] == -1 and imgNodeId[level][m, n] == -1:
        id = createNode()
        imgNodeId[level][x, y] = id
    elif imgNodeId[level][x, y] == -1 and imgNodeId[level][m, n] != -1:
        imgNodeId[level][x, y] = imgNodeId[level][m, n]
    elif imgNodeId[level][x, y] != imgNodeId[level][m, n]:
        mergeNode(level, imgNodeId[level][x, y], imgNodeId[level][m, n])

def createNode():
    global id
    id+=1
    return id
    
def mergeNode(level, Node_1_id, Node_2_id):
    for m in range(0, width):
        for n in range(0, height):
            if imgNodeId[level][m, n] == Node_2_id : imgNodeId[level][m, n] = Node_1_id

initialize()






