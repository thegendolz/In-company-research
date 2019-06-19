import alphathree
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np

Parent = []
#img = [[0, 1, 5, 12, 1],
#       [0, 1, 5, 12, 1],
#       [0, 1, 5, 12, 1],
#       [0, 1, 5, 12, 1],
#       [0, 1, 3, 2, 1]]
imgNodeId = []
id = 0
width = 5
height = 5

def initialize():
    #img = Image.open('image_1.jpg')
    #width, height = img.size;
    id = 0
    addEmptyLevel(0, width, height)

    ## Initialization of the alpha tree itself
    initializationAlphatree(width, height)

    #img.show()

def addEmptyLevel(level, width, height):
    if level == 0:
        imgNodeId.append(np.zeros((width, height)))
        for m in range(0, width):
            for n in range(0, height):
                imgNodeId[level][n, m] = -1
    else:
        imgNodeId.append(imgNodeId[level-1])

def initializationAlphatree(width, height):
    rootNotReached = True;
    ACC = 0
    while rootNotReached: #As long as root is not reached, keep going with a lower alpha-cc

        if ACC==3: rootNotReached = False
        for m in range(0, width):
            for n in range(0, height):
                lookForNeighbours(n, m, ACC, 4, width, height)

        reorganize(ACC)

        #print(imgNodeId[ACC])
        ACC+=1
        addEmptyLevel(ACC, 5, 5)

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
        directions = []
        if m - 1 >= 0 and abs(img[n][m] - img[n][m - 1]) <= alpha: directions.append('l')
        if m + 1 < width and abs(img[n][m] - img[n][m + 1]) <= alpha: directions.append('r')
        if n + 1 < height and abs(img[n][m] - img[n + 1][m]) <= alpha: directions.append('d')
        if n - 1 >= 0 and abs(img[n][m] - img[n - 1][m]) <= alpha: directions.append('u')
        #print(directions, n, m)
        updateNode(alpha, n, m, directions)
        #print(imgNodeId[0])

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


    #print(level)
    #print(imgNodeId[level][n, m])
    if (x == -1 and y == -1) or (imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] == -1):
        id = createNode()
        imgNodeId[level][n, m] = id
        #print("new node")
    elif imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] != -1:
        #print("copy")
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