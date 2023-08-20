#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char s[];
	int i, j, cnt=0;//cnt用于计算运算符的数量 
	gets(s);
	
	//用于删除空格 
	for(i=j=0; s[i]!='\0'; i++)
	{ 
		if(s[i]=='+'||s[i]=='-'||s[i]=='*'||s[i]=='/')
			cnt++;//计算符号数 
		if(s[i]!=' ') s[j++]=s[i];//删除空格 
	} 
	s[j]='\0';
	

		
	return 0;
}

void invert(char str[])
{
	int i,j,k;
	for(i=0, j=strlen(str)-1; i<j; i++, j--) 
	{
		k=str[i];
		str[i]=str[j];
		str[j]=k;
	}
}

void squeez(char)
