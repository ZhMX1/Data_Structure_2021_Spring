#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct st{
	int x;
	int *y;
}*pt;
int main()
{
	int a[]={1,2}, b[]={3,4};
	struct st c[2]= {10,a,20,b};
	pt = c;
	printf("%d\n",*pt->y);
	printf("%d\n",pt->x);
	printf("%d\n",++pt->x);
	printf("%d\n",(pt++)->x);
	return 0;
}


