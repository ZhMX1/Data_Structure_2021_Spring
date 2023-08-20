#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{	
	char numWord[550] = {'\0'};
	gets(numWord);
	int num = 0;
	int n = strlen(numWord);
	int i, j, mid = 0;
	for(i = 0; i < n; i++)
	{
		mid = numWord[i] - '0';
		for(j = 0; j < n-i-1; j++)
			mid *= 10;

		num += mid;
	}
	printf("%d", num);
	return 0;
}


