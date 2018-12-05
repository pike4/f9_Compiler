#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct inner {
		int a, b ;
};

struct outer {
		struct inner i;
		int g;
};

int add2 (struct inner  i)
{
	return  i .a +  i .b;

}

int add3 (struct outer  o)
{
	return  o .i.a +  o .i.b +  o .g;

}

int main() {

	struct outer st1;
	st1 .i.a = 1;
	st1 .i.b = 3;
	st1 .g = 4;
	add3(st1);
	char* temp0 = "st1.i.a: ";
	int temp1 = st1.i.a;
	char* temp2 = "; st1.i.b: ";
	int temp3 = st1.i.b;
	char* temp4 = "; st1.g: ";
	int temp5 = st1.g;
	printf("%s%d%s%d%s%d",temp0, temp1, temp2, temp3, temp4, temp5);
	char* temp6 = "\nAdd2: ";
	int temp7 = add2(st1.i);
	char* temp8 = "; Add3: ";
	int temp9 = add3(st1);
	char* temp10 = "\n";
	printf("%s%d%s%d%s",temp6, temp7, temp8, temp9, temp10);
	return 0;
}
