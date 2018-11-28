from genDefs import makeDefs
from genCode import genCode
from genKeywords import makeKeywords

makeDefs("states.dat", "../src/states.h")
makeDefs("tokens.dat", "../src/tokens.h")
makeDefs("actions.dat", "../src/actions.h")

makeKeywords()

genCode("../src/makeFSM.c")
