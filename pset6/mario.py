import cs50

def printLoop(n, toPrint):
    for i in range(n):
        print(toPrint, end="")

def printHashes(n):
    printLoop(n, "#")

def printSpaces(n):
    printLoop(n, " ")

def printHalfRow(n, half_row, isSecond):
    spaces = half_row - n

    if isSecond:
        printHashes(n)
        printSpaces(spaces)

    else:
        printSpaces(spaces)
        printHashes(n)

def makeMarioPyramid(height):
    for i in range(1, height):
        printHalfRow(i, height, False)
        printSpaces(2)
        printHalfRow(i, height, True)
        print("")

def getRowSpec():
    print("Input a height for the half pyramid: ", end="")
    height = cs50.get_int()
    if height <= 23 and height > 0:
        return height
    else:
        print("Please input an integer between 1 and 23 inclusive")
        exit(1)

def main():
    height = getRowSpec()
    makeMarioPyramid(height)

if __name__ == "__main__":
    main()






