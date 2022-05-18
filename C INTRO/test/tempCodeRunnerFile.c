#include <stdio.h>
#include <string.h>

int main()
{
	char ds[5][100] = {"TV127  31 inch Television", "CD057  CD Player", "TA877  Answering Machine", "CS409  Car Stereo", "PC655  Personal Computer"};
	char *sp;
	char masp[100];
	int i;

	printf("Nhap vao ma san pham: ");
	gets(masp);
	for (i = 0; i < 5; i++)
	{
		sp = strstr(ds[i], masp);
	}
	printf("San pham la: %s", sp);

	return 0;
}