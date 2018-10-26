def makeKeywords():
    import sys


    inF = open("keywords.dat", "r")
    outF = open("../keywords.h", "w")
    outF2 = open("../keywords.c", "w")

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
    outF.write("extern char* keywords[NUM_KEYWORDS];\n")
    outF.write("extern int keywordCodes[NUM_KEYWORDS];")

    outF2.write("#include \"keywords.h\"\n\n")
    outF2.write("char *keywords[" + str(count) + "] = { ")
    for i in range (0, count):
        outF2.write("\"" + names[i] + "\"")
        if(i < count - 1):
            outF2.write(", ")

    outF2.write("};\n")

	# Write KeywordCodes array initialization to c file
    outF2.write("int keywordCodes[" + str(count) + "] = { ")
    for i in range(0, count):
        outF2.write(vals[i])
        if(i < count - 1):
            outF2.write(", ")
    outF2.write("};\n")


    inF.close()
    outF.close()
    outF2.close()
