import alphathree
import matplotlib.pyplot as plt
from PIL import Image
import numpy as np
import time
from scipy.spatial import distance

Parent = []
Merges = []
# getImage = Image.open('example_1.png')
# img = np.asarray(getImage.convert('1'))
# width, height = getImage.size
img = [[0, 1, 1, 1, 6],
      [12, 1, 1, 26, 6],
      [0, 1, 9, 1, 6],
      [0, 1, 12, 1, 6],
      [0, 1, 1, 1, 6]]

width, height = 5, 5
imgNodeId = []
tuplesData = [[[-1 for z in range(4)] for j in range(width)] for i in range(height)]


dissimilarityMatrixHorizontal = []
dissimilarityMatrixVertical = []

id = 0

def initialize():
    start = time.time()


    #print(tuplesData)
    initializeAlphaTree()

    #addEmptyLevel(id)
    ## Initialization of the alpha tree itself
    #initializationAlphatree(width, height)
    #print(Merges)
    #addAlphaLayers()
    #getImage.show()

    end = time.time()

    print("Execution time:", end - start, "seconds")



def initializeAlphaTree():
    global id
    addEmptyLevel(0)
    for n in range(0, height):
        for m in range(0, width-1):
            dissHorizontal = calculateDissimilarity(img[n][m], img[n][m+1])
            dissimilarityMatrixHorizontal.append([n, m, dissHorizontal])
            if n < height-1:
                dissVertical = calculateDissimilarity(img[n][m], img[n + 1][m])
                dissimilarityMatrixVertical.append([n, m, dissVertical])

    #print(dissimilarityMatrixHorizontal)

    for diss in dissimilarityMatrixHorizontal:
        n = diss[0]
        m = diss[1]
        dissimilarity = diss[2]
        if dissimilarity == 0:
            if imgNodeId[0][n, m] == -1 and imgNodeId[0][n, m+1] != -1:
                #Check if has same otherwise add together
                imgNodeId[0][n, m] = imgNodeId[0][n, m+1]
                setTuples(n, m, n, m+1, tuplesData[n][m+1][2], tuplesData[n][m+1][3])
            elif imgNodeId[0][n, m] != -1 and imgNodeId[0][n, m+1] == -1:
                imgNodeId[0][n, m+1] = imgNodeId[0][n, m]
                setTuples(n, m+1, n, m, tuplesData[n][m][2], tuplesData[n][m][3])
            elif imgNodeId[0][n, m] != -1 and imgNodeId[0][n, m+1] != -1:
                union(n, m, n, m+1)
            else:
                imgNodeId[0][n, m] = id
                setTuples(n, m, -1, -1, n, m)
                imgNodeId[0][n, m+1] = id
                setTuples(n, m+1, n, m, n, m)
                id += 1
        else:
            imgNodeId[0][n, m] = id
            setTuples(n, m, -1, -1, n, m)
            id += 1

            imgNodeId[0][n, m+1] = id
            setTuples(n, m+1, -1, -1, n, m+1)
            id += 1

    print(imgNodeId[0])

    for diss in dissimilarityMatrixVertical:
        n = diss[0]
        m = diss[1]
        dissimilarity = diss[2]
        if dissimilarity == 0:
            if imgNodeId[0][n, m] != -1 and imgNodeId[0][n+1, m] != -1:
                union(n, m, n+1, m)
        elif imgNodeId[0][n+1, m] == -1:
            imgNodeId[0][n+1, m] = id
            setTuples(n+1, m, -1, -1, n+1, m)
            id += 1
    print(imgNodeId[0])

    #dissimilarityMatrixHorizontal.sort(key=lambda x: x[2])
    #print(dissimilarityMatrixHorizontal)
    #dissimilarityMatrixVertical.sort(key=lambda x: x[2])

def calculateDissimilarity(obj1, obj2):
    return abs(obj1 - obj2)

def setTuples(n, m, d, f, x, y):
    tuplesData[n][m] = [d, f, x, y]

def union(n,m,x,y):
    tuple1 = tuplesData[n][m]
    #tuple2 = tuplesData[x][y]

    while tuplesData[x][y][0] != -1 and tuplesData[x][y][1] != -1:
        tuple2 = tuplesData[x][y]
        imgNodeId[0][x, y] = imgNodeId[0][n, m]
        setTuples(x, y, n, m, tuple1[2], tuple1[3])
        x = tuple2[0]
        y = tuple2[1]

    setTuples(x, y, n, m, tuple1[2], tuple1[3])

def addEmptyLevel(level):
    if level == 0:
        imgNodeId.append(np.zeros((height, width)))
        for m in range(0, width):
            for n in range(0, height):
                imgNodeId[level][n, m] = -1

    #print(tuplesData)
#----------------------------------[Rewritten]------------------------------------------------

def initializationAlphatree(width, height):

    a = time.time()
    for m in range(0, width):
        for n in range(0, height):
            lookForNeighbours(n, m, 0, 4, width, height)
    #reorganize(ACC)

    print(imgNodeId[0])
    b = time.time()
    print("Execution time for loop:", b - a, "seconds")


def addAlphaLayers():
    ACC = 1
    rootNotReached = True
    while rootNotReached:
        addEmptyLevel(ACC)
        #for merge in uniques:


        a = time.time()
        # As long as root is not reached, keep going with a lower alpha-cc
        for m in range(0, width):
            for n in range(0, height):
                if m < width-1:
                    if imgNodeId[ACC][n, m+1] != imgNodeId[ACC][n, m] and getDistance(img[n][m], img[n][m + 1]) <= ACC:
                        Merges[ACC].append([imgNodeId[ACC][n, m+1],  imgNodeId[ACC][n, m]])
                        mergeNode(ACC, imgNodeId[ACC][n, m+1], imgNodeId[ACC][n, m])
                if n < height-1:
                    if imgNodeId[ACC][n+1, m] != imgNodeId[ACC][n, m] and getDistance(img[n][m], img[n + 1][m]) <= ACC:
                        Merges[ACC].append([imgNodeId[ACC][n+1, m],  imgNodeId[ACC][n, m]])
                        mergeNode(ACC, imgNodeId[ACC][n+1, m], imgNodeId[ACC][n, m])

        b = time.time()
        print("Alpha level:", ACC, "execution time:", b - a, "seconds")
        print(imgNodeId[ACC])
        print(Merges)
        if ACC == 10:
            rootNotReached = False
            #exit(1)
            # img.show()
        ACC+=1
    pillow_image = Image.fromarray(imgNodeId[10].astype('uint8'))
    pillow_image.show()

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
    #distance = abs(obj1[0] - (int(obj1[0]) + int(obj2[0])) / 2)
    #obj1 = obj1.astype(np.float32)
    #obj2 = obj2.astype(np.float32)
    distance = abs(obj1 - obj2)
    return distance

def updateNode(level, n, m, directions):
    x = -1; y = -1
    newDir = []
    for direction in directions:
        if direction == 'r' and imgNodeId[level][n, m+1] != -1:
            x = n
            y = m + 1
            newDir.append('r')
        if direction == 'l' and imgNodeId[level][n, m-1] != -1:
            x = n
            y = m - 1
            newDir.append('l')
        if direction == 'd' and imgNodeId[level][n+1, m] != -1:
            x = n + 1
            y = m
            newDir.append('d')
        if direction == 'u' and imgNodeId[level][n - 1, m] != -1:
            x = n - 1
            y = m
            newDir.append('d')

    if len(directions) == 0 or (imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] == -1) and len(newDir) == 0:
        id = createNode()
        Merges[level].append(id)
        imgNodeId[level][n, m] = id
    elif imgNodeId[level][n, m] == -1 and imgNodeId[level][x, y] != -1 and len(newDir) < 2:
        imgNodeId[level][n, m] = imgNodeId[level][x, y]
    else:
        imgNodeId[level][n, m] = imgNodeId[level][x, y]
        for direction in newDir:
            if direction == 'l':
                mergeNode(level, imgNodeId[level][n, m-1], imgNodeId[level][n, m])
            elif direction == 'r':
                mergeNode(level, imgNodeId[level][n, m+1], imgNodeId[level][n, m])
            elif direction == 'd':
                mergeNode(level, imgNodeId[level][n+1, m], imgNodeId[level][n, m])
            elif direction == 'u':
                mergeNode(level, imgNodeId[level][n-1, m], imgNodeId[level][n, m])
            break

def createNode():
    global id
    id+=1
    return id
    
def mergeNode(level, Node_1_id, Node_2_id):
    for m in range(0, width):
        for n in range(0, height):
            if imgNodeId[level][n, m] == Node_2_id : imgNodeId[level][n, m] = Node_1_id

initialize()