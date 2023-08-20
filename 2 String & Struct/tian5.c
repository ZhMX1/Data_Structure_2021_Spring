#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	struct{
		int x;
		char *y;
	}tab[2]={{1,"ab"},{2,"cd"}},*p = tab;
	printf("%c",*(++p)->y); 

	return 0;
}


