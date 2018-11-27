#include <stdio.h>
#include <stdlib.h>

int main() {

	int w = 0, h = 0 , x = 0 , y = 0 ;
	char* temp0 = "Enter an integer for the width and the height\n";
	printf("%s",temp0);
	scanf("%d%d",&w,&h);	while( x  <  h ) {
		y  = 0;
		while( y  <  w ) {
			char* temp1 = "*";
			printf("%s",temp1);
			y  =  y  + 1;

		}
		char* temp2 = "\n";
		printf("%s",temp2);
		x  =  x  + 1;

	}
	int temp3 =  w ;
	int temp4 =  h ;
	printf("%d%d",temp3, temp4);
	return 0;
}
