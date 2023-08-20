#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
void swap(int *p, int *q)
{
	int *t;
	t=p;
	p=q;
	q=t;
}
main()
{
	int a=10,b=20;
	
	swap(&a,&b);
	printf("a=%d,b=%d\n",a,b);

	return 0;
}


