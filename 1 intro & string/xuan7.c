#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int try(int );
int main()
{
	int x;
	x = try(5);
	printf("%d\n",x);
	return 0;
}
int try(int n){
	if(n>0)
	return (n*try(n-2));
	else
	return (1);
}
