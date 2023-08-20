#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>    
#include<string.h>
int main()
{
	char s[150], p[150];
	int n=0, i, p1=0, p2=0;
	int t1=0 ,t2=0, cnt=0; 
	
	gets(s);

	//判断一下小数点p1和第一个非零数字p2位置 
	for(i=0; s[i]!='\0'; i++)
	{
		if(s[i]!='.'&&t1==0)	p1++;
		else t1++;
		
		if((s[i]=='0'||s[i]=='.')&&t2==0)	p2++;
		else t2++;
	}

	for(i=0; i <= p2 ; i++) p[i] = s[i];//s[i]!='\0'
	p[p2+1] = '.';
	for(i=p2+1; s[i]!='\0'; i++) p[i+1] = s[i];
	//在数列中（第一个非零数字后）插入一个新的合适的小数点
	//这一步做完可能有两个小数点 
	
	n=strlen(p);
	p[n] = 'e';
	
	for(i=p2; p[i]!='\0'; i++)
	{
		if(p[i]>='0'&&p[i]<='9')	printf("%c", p[i]);
		else if(p[i]=='.' && cnt==0 && p[i+1]!='e')
		{
			printf("%c", p[i]);
			cnt++;
		} 
	} 
	
	if(p1<p2) printf("e-%d", p2-p1);
	else printf("e%d", p1-p2-1);

	return 0;
}

