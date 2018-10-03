from genDefs import makeDefs
from genCode import genCode
from genKeywords import makeKeywords

makeDefs("tokens.dat", "../tokens.h")
makeDefs("states.dat", "../states.h")
makeDefs("actions.dat", "../actions.h")

makeKeywords()

genCode("../makeFSM.c")
