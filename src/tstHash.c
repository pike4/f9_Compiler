
void testHash()
{
	#define TESTMAX 3000
	char str[TESTMAX][20];
	int vals[TESTMAX];
	srand(time(0));

	for(int i = 0; i < TESTMAX; i++)
	{
		printf("i = %d\n", i);
		for(int j = 0; j < 20; j++)
		{
			str[i][j] = (rand() % 90) + 32;
		}
		str[i][19] = 0;

		hashInsert(str[i], i);
	}
	printf("done inserting\n");

	for(int i = 0; i < TESTMAX; i++)
	{
		int* suicide = 0;
		int res = hashGet(str[i]);

		if(res != i)
		{
			printf("at %d, goodbye\n", i);
			*suicide = 1;
		}
	}
}
