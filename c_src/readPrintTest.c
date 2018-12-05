#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct test {
		int a;
		int b;
};

struct badType {
		char c;
		char s[50];
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
	char s1[50], s2[50];
	int i1 = 0, i2 = 0 ;
	struct badType b;
	c1  =  'a' ;
	c2  =  c1 ;
	i1  = 1 + 2 + 1 + 1;
	i2  =  i1 ;
	strcpy(s2, "words");
	strcpy(s1, s2);
	strcpy(b.s, s1);
	b .c =  'a' ;
	b .i = 1 + 1 + 1 * (12 * 12);
	char* temp1 = "b.i: ";
	int temp2 = b.i;
	char* temp3 = " b.c: ";
	char temp4 = b.c;
	char* temp5 = " b.s: ";
	char* temp6 = b.s;
	char temp7 = '\n';
	printf("%s%d%s %c%s%s %c",temp1, temp2, temp3, temp4, temp5, temp6, temp7);
	char* temp8 = "Enter c1: char, i1: int, b.i:";
	printf("%s",temp8);
	char* temp9 = " int, b.c:char, b.s:string, s1:string";
	printf("%s",temp9);
	scanf(" %c%d%d %c%s%s",&c1,&i1,&b.i,&b.c,b.s,s1);
	char* temp10 = "c1:\t";
	char temp11 = c1;
	char* temp12 = "\ni1:\t";
	int temp13 =  i1  + 1;
	char* temp14 = "\nb.i:\t";
	int temp15 = b.i;
	char* temp16 = "\nb.c:\t";
	char temp17 = b.c;
	char* temp18 = "\nb.s\t";
	char* temp19 = b.s;
	char* temp20 = "\ns1\t";
	char* temp21 = s1;
	char temp22 = '\n';
	printf("%s %c%s%d%s%d%s %c%s%s%s%s %c",temp10, temp11, temp12, temp13, temp14, temp15, temp16, temp17, temp18, temp19, temp20, temp21, temp22);
	return 0;
}
