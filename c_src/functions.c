#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int foo (int a, char b, char* c)
{
	int y = 0;
	int u = 0;
	u  =  y ;
	return 9;

}

int bar (int a, char b, int c)
{
	char h[50];
	if(  a  > 10) {
		c  = 3;
		return  c ;

	}
	else {
		c  = foo(1 + 2, '1', "1+2");
		int temp0 =  c ;
		char* temp1 = "\n";
		printf("%d%s",temp0, temp1);
		c  = foo( a , b, h);
		int temp2 =  c ;
		char temp3 = '\n';
		printf("%d %c",temp2, temp3);
		c  = foo(foo(1, 'a', "a"), 'a', "a");
		int temp4 =  c ;
		char temp5 = '\n';
		printf("%d %c",temp4, temp5);
		return  c  + 1;

	}

}

int main() {

	int q = 0;
	q  = bar(1, '0', 1);
	exit(1);
	return 0;
}
