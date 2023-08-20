#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char s1[100]={0}, s2[100]={0};
	int l1, l2, n;
	int a[90]={0}, b[90]={0}, c[90]={0}, i, j;//a的数比b的数大 

	gets(s1);
	gets(s2);
	//注意此处的高位为0要处理一下字符串
	for(i = 0; s1[i]!='\0'; i++)
	{
		if(s1[i]!='0')	break;
		else
		{
			for(j = i; s1[j]!='\0'; j++)
				s1[j] = s1[j+1];
			i--;	
		}		
	} 
	//printf("%s\n", s1);
	for(i = 0; s2[i]!='\0'; i++)
	{
		if(s2[i]!='0')	break;
		else
		{
			for(j = i; s2[j]!='\0'; j++)
				s2[j] = s2[j+1];
			i--;	
		}			
	} 
	//printf("%s\n", s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	//先判断哪个数字更大一些，大的给a，小的给b 
	//把字符串转变成 倒序 整型数组，实现从最后一位开始减 
	if(l1<l2 || (l1==l2 && strcmp(s1,s2)<0)) //s2>s1  
	{
		n=l2;
		for(i=l1-1, j=0; i>=0; i--, j++)
			b[j] = s1[i]-'0';
		for(i=l2-1, j=0; i>=0; i--, j++)
			a[j] = s2[i]-'0';
		printf("-");
	}
	else//s1>=s2
	{
		n=l1;
		for(i=l1-1, j=0; i>=0; i--, j++)
			a[j] = s1[i]-'0';
		for(i=l2-1, j=0; i>=0; i--, j++)
			b[j] = s2[i]-'0';
	}
	//接下来对ab进行处理 
	int jie=0;
	for(i=0; i<n; i++)
	{
		if(a[i]<b[i]+jie)
		{
			c[i]=a[i]+10-b[i]-jie;
			jie=1;
		}
		else
		{
			c[i]=a[i]-b[i]-jie;
			jie=0;
		}	
	}
	
	int cnt=0;//倒序输出 
	for(i=n; i>=0; i--)
	{
		if(c[i]!=0||(c[i]==0&&cnt!=0))
		{
			printf("%d", c[i]);
			cnt++;	
		}
	} 
	if(cnt==0) printf("0");
	return 0;
}

