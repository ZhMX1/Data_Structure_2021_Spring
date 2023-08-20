#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
main()
{
	int a[4] = {1,2,3,4};
	int *p;
	p=&a[2];
	printf("%d",++*p);
	printf("%d\n",*--p);
}


