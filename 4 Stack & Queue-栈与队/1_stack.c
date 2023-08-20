#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int op = 0;
	int num = 0;
	int stack[200] = {0};
	int top = 0;//Õ»¶¥ÊÇ100 top<=100 
	scanf("%d", &op);
	while(op+1)
	{
		if(op == 1 )
		{
			if(top<100)
			{
				scanf("%d", &num);
				stack[++top] = num;
			}
			else	printf("error ");
		}
		else if(op == 0)
		{
			if(top > 0)
			{
				printf("%d ", stack[top]);
				top--;
			}
			else	printf("error ");
		}
		
		scanf("%d", &op);
	}
	return 0;
}

