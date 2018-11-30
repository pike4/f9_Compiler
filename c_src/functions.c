#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int foo (int a, char b, char* c)
{
	int y = 0;
	int u = 0;
	u  =  y ;

}

int bar (int a, char b, int c)
{
	char h[50];
	if(  a  <  b ) {
		c  = 3;
		return  c ;

	}
	else {
		c  = foo(1 + 2, '1', "1+2");
		c  = foo( a , b, h);
		c  = foo(foo(1, 'a', "a"), 'a', "a");
		return  c  + 1;

	}

}

int main() {

	int q = 0;
	q  = 0;
	exit(1);
	return 0;
}
