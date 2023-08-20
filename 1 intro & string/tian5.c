#include<stdio.h>
void func(char *q)
{
	char a[]="hello";
	q=a;
}
main()
{
	char *p;
	func(p);
	
	printf("%s\n", p);
}

