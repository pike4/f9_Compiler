
def genCode(outName):
    import sys

    inF = open("fsm.dat", 'r')
    outF = open(outName, 'w')

    outF.write("#include \"tokens.h\"\n")
    outF.write("#include \"actions.h\"\n")
    outF.write("#include \"states.h\"\n")
    outF.write("#include \"tok.h\"\n")

    outF.write("void makeFSM()\n{\n")
    outF.write("\t int i;\n")

    line = inF.readline()
    while(line):
        if len(line) < 2:
            line = inF.readline()
            continue
        words = str.split(line, ' ')
        #New state definition
        if len(words) == 1:
            curState = words[0][:-1]
            outF.write("\n\t//" + curState + "\n")
        else:
            charIndex = words[0]
            nextState = words[1]
            action = words[2]

            if len(words) == 4:
                retVal = words[3][:-1]
            else:
                action = words[2][:-1]
                retVal = "LEX_UNUSED"

            if(charIndex == "any"):
                outF.write("\tfor( i = 0; i < 256; i++)\n\t{\n")
                outF.write("\t\tstates[" + curState+ "][i].nextState = " + nextState + ";\n")
                outF.write("\t\tstates[" + curState + "][i].action = " + action + ";\n")
                outF.write("\t\tstates[" + curState + "][i].value = " + retVal + ";\n\t}\n\n")

            elif( charIndex[0] != '\'' and len(str.split(charIndex, '-')) > 1 ):
                indeces = str.split(charIndex, '-')
                outF.write("\tfor( i = \'" + indeces[0] +"\'; i <= \'" + indeces[1] + "\'; i++)\n\t{\n")
                outF.write("\t\tstates[" + curState+ "][i].nextState = " + nextState + ";\n")
                outF.write("\t\tstates[" + curState + "][i].action = " + action + ";\n")
                outF.write("\t\tstates[" + curState + "][i].value = " + retVal + ";\n\t}\n\n")
            
            else:
                outF.write("\tstates["+curState+"][" + charIndex + "].nextState = " + nextState + ";\n")
                outF.write("\tstates["+curState+"][" + charIndex + "].action = " + action + ";\n")
                outF.write("\tstates["+curState+"][" + charIndex + "].value = " + retVal + ";\n\n")

        line = inF.readline()

    outF.write("}\n")
        
    outF.close()
    inF.close()
