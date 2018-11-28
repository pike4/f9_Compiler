#include <stdio.h>
#include <stdlib.h>

struct test {
		int a;
		int b;
};

struct badType {
		char f;
};

int fun (struct test  a)
{
	int temp0 =  a .a;
	printf("%d",temp0);

}

int main() {

	struct test g;
	struct badType h;
	g .a = 5;
	fun(g);
	char* temp1 = "\n";
	printf("%s",temp1);
	return 0;
}
