#include <stdio.h>
#include <stdlib.h>

struct test {
		int a;
		int b;
};

struct badType {
		char c;
		char* s;
		int i;
};

int retZero ()
{
	return 0;

}

int fun (struct test  a)
{
	int temp0 = a.a;
	printf("%d",temp0);

}

int main() {

	char c1 = 0, c2 = 0 ;
	char* s1 = malloc(100), *s2 = 0 ;
	int i1 = 0, i2 = 0 ;
	struct badType b;
	c1  =  'a' ;
	c2  =  c1 ;
	s1  =  "a" ;
	s2  =  s1 ;
	i1  = 1 + 2 + 1 + 1;
	i2  =  i1 ;
	b .s =  "hellot" ;
	b .c =  'a' ;
	b .i = 1 + 1 + 1 * (12 * 12);
	char* temp1 = "b.i: ";
	int temp2 = b.i;
	char* temp3 = " b.c: ";
	char temp4 = b.c;
	char* temp5 = " b.s: ";
	char* temp6 = b.s;
	char temp7 = '\n';
	int temp8 = retZero();
	int temp9 = 1;
	int temp10 = 1 + 2 + 2 + 2;
	printf("%s%d%s%c%s%s%c%d%d%d",temp1, temp2, temp3, temp4, temp5, temp6, temp7, temp8, temp9, temp10);
	scanf("%c%d%d%c",&c1,&i1,&b.i,&b.c);
	char* temp11 = "c1 ";
	char temp12 = c1;
	char* temp13 = "i1 ";
	int temp14 =  i1 ;
	char* temp15 = "b.i: ";
	int temp16 = b.i;
	char* temp17 = " b.c: ";
	char temp18 = b.c;
	char temp19 = '\n';
	printf("%s%c%s%d%s%d%s%c%c",temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19);
	return 0;
}
