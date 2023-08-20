#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char c[]="\t\v\\\0will\n";
	printf("%d",strlen(c));	
	return 0;
}

