#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int x[10] = {0,1,2,3,4,5,6,7,8,9}, *p1, *p2, *p3;
	p1 = x+3;
	p2 = x+2;
	p3 = x+2;

	printf("%d %d %d %d",x[3], *p1++, *(p2++), *++p3);

	return 0;
}


