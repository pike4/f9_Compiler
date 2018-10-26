from genDefs import makeDefs
from genCode import genCode
from genKeywords import makeKeywords

makeDefs("states.dat", "../states.h")
makeDefs("tokens.dat", "../tokens.h")
makeDefs("actions.dat", "../actions.h")

makeKeywords()

genCode("../makeFSM.c")
