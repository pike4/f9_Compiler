def makeKeywords():
    import sys

    inF = open("keywords.dat", "r")
    outF = open("../keywords.h", "w")

    outF.write("#include \"tokens.h\"\n")

    line = inF.readline()

    names = []
    vals = []
    count = 0
    
    while(line):

        if len(line) < 2:
            break

        line = line[:-1]

        words = str.split(line)

        if(len(words) < 2):
            continue
        
        names.append(words[0])
        vals.append(words[1])
        count += 1

        line = inF.readline()
    outF.write("#define NUM_KEYWORDS " + str(count) + "\n\n")

    outF.write("char *keywords[" + str(count) + "] = { ")

    for i in range (0, count):
        outF.write("\"" + names[i] + "\"")
        if(i < count - 1):
            outF.write(", ")

    outF.write("};\n")

    outF.write("int keywordCodes[" + str(count) + "] = { ")
    for i in range(0, count):
        outF.write(vals[i])
        if(i < count - 1):
            outF.write(",")
    outF.write("};\n")


    inF.close()
    outF.close()
