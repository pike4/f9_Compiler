

def makeDefs(inName, outName):
    import sys

 
	#Open the files  
    inF = open(inName, 'r')
    outF = open(outName, 'w')

	#Open a second file as a c file of the same base name
    outName2 = outName[:-1] + "c"
    outF2 = open(outName2, 'w')

	#Declarations
    cnt = 0
    names = []

 
	#Remove leading directory from output file name
    while(outName[0] == '.' or outName[0] == '/'):
        outName = outName[1:]
    
    mainName = str.split(inName, '.')[0]
    defName = mainName.upper() + "_DEF"
    arrayName = mainName + "_names"
    line = inF.readline()
    while(line):
        if len(line) < 2:
            break
        line = line[:-1]
        names.append(line)
        line = inF.readline()
        cnt = cnt + 1


    for x in range(0, len(names)):
        outF.write('#define ' + names[x] + ' ' + str(x) + '\n')

    outF.write("\nchar* " + arrayName + "[" + str(len(names)) + "];\n")

    outF2.write("#include \"" + outName + "\"\n")
    outF2.write("\nchar* " + arrayName + "[" + str(len(names)) + "] = \n{\n")

    for x in range(0, len(names)):
        outF2.write("\t\"" + names[x] + "\"")
        if x < len(names) - 1:
            outF2.write(",")
        outF2.write("\n")

    outF2.write("};\n")
        
    outF.close()
    outF2.close()
    inF.close()
