import alphathree
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import time
from scipy.spatial import distance

Parent = []
getImage = Image.open('example_1.png')
img = np.asarray(getImage.convert('HSV'))
imgNodeId = []
id = 0
width, height = getImage.size;

def initialize():
    start = time.time()
    addEmptyLevel(id)

    ## Initialization of the alpha tree itself
    initializationAlphatree(width, height)

    #getImage.show()

    end = time.time()

    print("Execution time:", end - start, "seconds")

def addEmptyLevel(level):
    if level == 0:
        imgNodeId.append(np.zeros((height, width)))
        for m in range(0, width):
            for n in range(0, height):
                imgNodeId[level][n, m] = -1
    else:
        imgNodeId.append(imgNodeId[level-1])

def initializationAlphatree(width, height):
    rootNotReached = True;
    ACC = 0
    while rootNotReached: #As long as root is not reached, keep going with a lower alpha-cc

        for m in range(0, width):
            for n in range(0, height):
                lookForNeighbours(n, m, ACC, 4, width, height)

        #reorganize(ACC)

        print("ACC")
        #print(imgNodeId[ACC])
        if ACC == 1:
            rootNotReached = False
            #img.show()

        ACC += 1
        addEmptyLevel(ACC)

def reorganize(level):
    id = 1
    lst = np.unique(imgNodeId[level])

    for item in lst:
        for m in range(0, width):
            for n in range(0, height):
                if imgNodeId[level][n, m] == item: imgNodeId[level][n, m] = id
        id+=1

def lookForNeighbours(n, m, alpha, CNNType, width, height):
    if(CNNType == 4):
        #print(n, m)
        directions = []
        if m - 1 >= 0 and getDistance(img[n][m], img[n][m - 1]) <= alpha: directions.append('l')
        if m + 1 < width and getDistance(img[n][m], img[n][m + 1]) <= alpha: directions.append('r')
        if n + 1 < height and getDistance(img[n][m],img[n + 1][m]) <= alpha: directions.append('d')
        if n - 1 >= 0 and getDistance(img[n][m], img[n - 1][m]) <= alpha: directions.append('u')
        updateNode(alpha, n, m, directions)

def getDistance(obj1, obj2):
    distance = abs(obj1[0] - (int(obj1[0]) + int(obj2[0])) / 2)
    return distance

def updateNode(level, n, m, directions):
    x = -1; y = -1
    for direction in directions:
        if direction == 'l':
            x = n
            y = m - 1
        if direction == 'r':
            x = n
            y = m + 1
        if direction == 'd':
            x = n + 1
            y = m
        if direction == 'u':
            x = n - 1
            y = m

    if (x == -1 and y == -1) or (imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] == -1):
        id = createNode()
        imgNodeId[level][n, m] = id
    elif imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] != -1:
        imgNodeId[level][n, m] = imgNodeId[level][x, y]
    else:
        for direction in directions:
            if direction == 'l':  mergeNode(level, imgNodeId[level][n, m], imgNodeId[level][n, m-1])
            if direction == 'r':  mergeNode(level, imgNodeId[level][n, m], imgNodeId[level][n, m+1])
            if direction == 'd':  mergeNode(level, imgNodeId[level][n, m], imgNodeId[level][n+1, m])
            if direction == 'u':  mergeNode(level, imgNodeId[level][n, m], imgNodeId[level][n-1, m])

def createNode():
    global id
    id+=1
    return id
    
def mergeNode(level, Node_1_id, Node_2_id):
    for m in range(0, width):
        for n in range(0, height):
            if imgNodeId[level][n, m] == Node_2_id : imgNodeId[level][n, m] = Node_1_id

initialize()