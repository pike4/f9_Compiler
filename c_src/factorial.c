#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main() {

	int in = 0, tmp = 0 , out = 0 ;
	char* temp0 = "Enter a number to compute its factorial";
	printf("%s",temp0);
	scanf("%d",&in);
	out  = 1;
	tmp  =  in ;
	while( in  > 1) {
		out  =  out  *  in ;
		in  =  in  - 1;

	}
	char* temp1 = "Factorial of ";
	int temp2 =  tmp ;
	char* temp3 = " is ";
	int temp4 =  out ;
	char* temp5 = "\n";
	printf("%s%d%s%d%s",temp1, temp2, temp3, temp4, temp5);
	return 0;
}
