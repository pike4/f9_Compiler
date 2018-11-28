#include <stdio.h>
#include <stdlib.h>

int ackermann (int m, int n)
{
	if(  m  == 0) {
		return  n  + 1;

	}
	else {
		if(  n  == 0) {
			return ackermann( m  - 1, 1);

		}
		else {
			return ackermann( m  - 1, ackermann( m ,  n  - 1));

		}

	}

}

int main() {

	int a = 0, b = 0 , c = 0 ;
	char* temp0 = "Enter 2 numbers to compute";
	char* temp1 = " the ackermann function for them";
	printf("%s%s",temp0, temp1);
	scanf("%d%d",&b,&c);
	a  = ackermann( b ,  c );
	char* temp2 = "Ackermann(";
	int temp3 =  b ;
	char* temp4 = ", ";
	int temp5 =  c ;
	char* temp6 = ") = ";
	int temp7 =  a ;
	char* temp8 = "\n";
	printf("%s%d%s%d%s%d%s",temp2, temp3, temp4, temp5, temp6, temp7, temp8);
	return 0;
}
