#include <stdio.h>
#include <stdlib.h>

int main() {

	int w = 0, h = 0 , x = 0 , y = 0 ;
	printf("Enter an integer for the width and the height\n");
 	scanf("%d%d",&w,&h);	while( x  <  h ) {
		y  = 0;
		while( y  <  w ) {
			printf("*");
 			y  =  y  + 1;

		}
		printf("\n");
 		x  =  x  + 1;

	}
	printf("%d",  w );
	printf("%d",  h );
	return 0;
}
