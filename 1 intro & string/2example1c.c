#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int a1, a2, a3, sum=0;
	char f1, f2, f3;
	//scanf("%d %c", &a1, &f1);
	a1=0;
	f1='+'; //初始化 
	//用加减符号把整个等式分为数个部分（单元） 
	//外层循环判断加减（对单元），内层循环计算单元内部乘除 
	while(f1!='=')
	{
		//scanf("%d %c", &a2, &f2);
		scanf("%d %c", &a2, &f2);
		while(f2=='*'||f2=='/')	
		{
			scanf("%d %c", &a3, &f3);
			if(f2=='*')
				a2 *= a3;
			else if(f2=='/')
				a2 /= a3;
			f2 = f3;
		}//判断一个连乘除的部分 
	
		if(f1 == '+')
			sum += a2;
		else if(f1 == '-')
			sum -= a2;
		f1 = f2;
	}	
	printf("%d", sum);
	//if(f1=='=') printf("%d", sum);	

	return 0;
}


