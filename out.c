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

	int _test_val = 0, hello = 0 , woo = 0 ;
	int should_err = 0, probably = 0 , i = 0 ;
	char aChar = 0;
	char* aString = 0, bString = 0 ;
	struct myStruct init1;
	struct myStruct2 init2;
	while( i  < 2) {
		printf("\"hello\"\n");
 		printf("%d",  i );
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
 		printf("%d",  init1 .a);
		printf("%d",  init2 .m1.b);

	}
	return 0;
}
