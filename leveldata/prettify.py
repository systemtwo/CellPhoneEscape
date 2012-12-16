import sys

if (len(sys.argv) != 2):
    print "Useage:"
    print ""
    print "prettify.py <file>"
    print "Will make file look nice if there are mismatched number lengths"
    print ""
    print "Example:"
    print "0 0 0 -1 0"
    print "0 0 0 0 0"
    print ""
    print "To"
    print "00 00 00 -1 00"
    print "00 00 00 00 00"
else:
    f = open(sys.argv[1])
    string = ""
    maxlength = 0
    levelarray = []
    colcount = 0
    rowcount = 0
    
    string += f.readline()
    for line in f:
        #Find the max length of numstring and also store the array for future access
        temp = line.rstrip().split(" ")
        levelarray.append(temp)
        print temp
        for i in temp:
            if (len(i) > maxlength):
                maxlength = len(i)

    #Set up printf equivilant
    template = "%0" + str(maxlength) + "d"
    for i in levelarray:
        for j in i:
            levelarray[rowcount][colcount] = template % (int(j),)
            colcount += 1
        rowcount += 1
        colcount = 0

    #Set up to print to file (Should be merged with above step
    for i in levelarray:
        for j in i:
            string += j + " "
        string += "\n"
    
    g = open(sys.argv[1].split(".")[0] + "p.txt", "w")
    g.write(string)
