#include <stdio.h>
#include <stdlib.h>

struct myStruct {
		int a, b , c ;
		int d;
		char f;
};

struct myStruct2 {
		struct myStruct m1;
		int size;
};

int main() {

	int _test_val , hello, woo;
	int should_err , probably, i;
	char aChar ;
	char* aString , bString;
	struct myStruct init1;
	struct myStruct2 init2;
	while( i  < 200) {
		printf("\"hello\"\n");
 		i  += 20;

	}
	_test_val  = 100;
	i  =  init1 .a +  init2 .m1.f * 100;
	i  = 100 / 10;
	aChar  =  '\n' ;
	aString  =  "hello" ;
	if(  i  < 0) {
		exit(0);

	}
	else {
		printf("all good\n");
 		printf("%d", 1 + 1);
		printf("forU");
 
	}
	return 0;
}
