#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct list{
	char c;
	struct list *next; 
};
int main()
{
	char s[50]={'\0'};
	gets(s);
	int i = 0, j = 0, l;
	int flag[30]={0};
	
	l = strlen(s);
	for(i=0; i<l; i++)//j������key�����հ����� 
	{
		if(flag[s[i] - 'a'] == 0)
		{
			s[j++] = s[i];
			flag[s[i] - 'a'] = 1;
		}
	}
	//��ȫ��ĸ 
	for(i = 0; i < 26; i++)
	{
		if(flag[i]==0)
			s[j++] = 'a' + i;	
	}
	puts(s);
	
/*	struct list *head = NULL, *p, *q;
	for(i = 0; i<26; i++)
	{
		q=(struct list *)malloc(sizeof(struct list));
		q->c = s[i];
		q->next = NULL;//���µĴ���ռ� 

		if(head == NULL)
			head = p = q;
		else{
			p->next = q;
			p = p->next;
	}*/
	return 0;
}


