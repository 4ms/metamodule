import re

def prepareSourceFile(filename):
    with open(filename, "wr") as fil:
        src = fil.read()
        fil.write(src)
        


