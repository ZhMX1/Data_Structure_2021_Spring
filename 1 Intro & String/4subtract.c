#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	char s1[100]={0}, s2[100]={0};
	int l1, l2, n;
	int a[90]={0}, b[90]={0}, c[90]={0}, i, j;//a������b������ 

	gets(s1);
	gets(s2);
	//ע��˴��ĸ�λΪ0Ҫ����һ���ַ���
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
	//���ж��ĸ����ָ���һЩ����ĸ�a��С�ĸ�b 
	//���ַ���ת��� ���� �������飬ʵ�ִ����һλ��ʼ�� 
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
	//��������ab���д��� 
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
	
	int cnt=0;//������� 
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

