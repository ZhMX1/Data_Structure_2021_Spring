#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>


int main()
{
	int n, a[15]={0}, jinwei=0;
	int i, j, cnt=0, flag=0, t=0;
	
	scanf("%d", &n);
	while(a[14-n]==0)
	{
	/*�ȴ���a ,�߾��ȼӷ���1*/ 
	if(a[14]!=9)
		a[14]++;
	else 
	{
		a[14] = 0;
		jinwei = 1;
	} 
	for(i=13; i>0; i--)
	{	
		if(a[i] != 9)
		{
			a[i] = a[i]+jinwei;
			jinwei = 0;
		} 
	
		else
		{
			if(jinwei==1)
			{
				a[i] = 0;
				jinwei = 1;
			} 
		}
	}
	for(i=14; i>14-n; i--)
				printf("%d ", a[i]);
				printf("\n");
	/*�ж�a���ǲ���ÿһ������(j)������һ�飬�ǲ��Ǵ���n����Ϊ0*/ 
	/*	for(j=1; j<=n; j++)
		{
			for(i=14; i>14-n; i--)
			{
				if(a[i]==j)
					cnt++;
				if(a[i]==0||a[i]>n)
				{
					flag++;
					break;
				}
			} 
			if(flag!=0||cnt!=1)	break;
			if(cnt==1) t++;
			cnt = 0;
			flag = 0;
		}
		if(t==n)
		{
			for(i=14-n+1; i<=14; i--)
				printf("%d ", a[i]);
			printf("\n");
		}
		t=0;*/
	}
	
	printf("finish");
	return 0;
}

/*void jia1(int a[15]){
	int i, jinwei=0;
	if(a[15]!= 9)
		a[15] = a[15]+1;
	else {
		a[15] = 0;
		jinwei = 1;
	} 
	for(i=14; i>0; i--)
	{	
		if(a[i] != 9)
		{
			a[i] = a[i]+jinwei;
			jinwei = 0;
		} 
	
		else
		{
			if(jinwei==1)
			{
				a[i] = 0;
				jinwei = 1;
			} 
		}
	}
}*/
