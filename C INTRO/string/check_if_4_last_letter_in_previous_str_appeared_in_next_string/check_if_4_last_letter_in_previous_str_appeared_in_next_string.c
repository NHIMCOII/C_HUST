#include <stdio.h>
#include <string.h>
//word with 5 letter.
int check(char *a, char *b)
{
	int c[26], d[26];
	int i, count = 0, k;

	for (i = 0; i < 26; i++)
	{
		c[i] = 0;
		d[i] = 0;
	}
	for (i = 1; i < 5; i++)
	{
		k = a[i] - 97;
		c[k]++;
	}

	for (i = 0; i < 5; i++)
	{
		k = b[i] - 97;
		d[k]++;
	}
	for (i = 0; i < 26; i++)
	{
		if (d[i] > 0 && c[i] > 0)
		{
			if ((d[i] - c[i]) >= 0){
				while(c[i]>1){
					count++;
					d[i]--;c[i]--;
				}
				count++;
			}
		}
	}

	if (count == 4)
		return 1;
	return 0;
}

int main()
{
	char a[6], b[6];
	int x;
	printf("Enter string 1: ");
	gets(a);
	printf("Enter string 2: ");
	gets(b);
	x = check(a, b);
	printf("%d", x);
	return 0;
}