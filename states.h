#define STATE_INIT 0
#define STATE_SLASH 1
#define STATE_SLASH_SLASH 2
#define STATE_SLASH_STAR 3
#define STATE_SLASH_STAR_STAR 4
#define STATE_IDENT 5
#define STATE_NUM 6
#define STATE_ZERO 7
#define STATE_ZERO_X 8
#define STATE_HEX 9
#define STATE_LT 10
#define STATE_GT 11
#define STATE_EQ 12
#define STATE_PLUS 13
#define STATE_MIN 14
#define STATE_MUL 15
#define STATE_NOT 16
#define STATE_AND 17
#define STATE_OR 18
#define STATE_QUOTE 19
#define STATE_ESCAPE 20
#define NUM_STATES 21

char* states_names[22];
