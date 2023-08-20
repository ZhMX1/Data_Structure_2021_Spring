#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 100

struct list{
	char c;
	struct list *next; 
};

void establish_key1(char s[max]);
int main()
{
	char s[max];
	establish_key1(s);
	
	FILE *fp1 = fopen("in.txt","r");
	FILE *fp2 = fopen("in_crpyt.txt","w");
	
	int i , j , l;
	struct list *head = NULL, *p, *q;
	for(i = 0; i< 95; i++)
	{
		q=(struct list *)malloc(sizeof(struct list));
		q->c = s[i];
		q->next = NULL;//开新的储存空间 

		if(head == NULL)
			head = p = q;
		else{
			p->next = q;
			p = p->next;
		}
	}
	p->next = head;
	q = head;
	
	char key[150] = {'\0'};
	int asc = 0;
	int all = 95;
	int move = 0;
	int asc0 = q->c;
	while(all-1)
	{
		asc = q->c;
		p->next = p->next->next;
		free(q);
		q = p->next;
		all--;
		move = asc % all;
		
		if(move!=0)
			for(i = 0; i < move - 1; i++){
				p = p->next;
				q = q->next;
			}
		else
			for(i = 0; i < asc - 1; i++){
				p = p->next;
				q = q->next;
			}
		key[asc] = q->c;
	}
	asc = q->c;
	key[asc] = asc0;
	
//	for(i = 32; i<=126; i++)
//		printf("%c", key[i]);
	
	int zifu = '\0';
	zifu = fgetc(fp1);
	while(zifu != EOF)
	{
		if (zifu > 126 || zifu < 32)
			fprintf(fp2, "%c", zifu);
		else 
			fprintf(fp2, "%c", key[zifu]);
		zifu = fgetc(fp1);
	}
	
	fclose(fp1);
	fclose(fp2);
	
	return 0;
}

void establish_key1(char s[max])
{
	gets(s);
	
	int i = 0, j = 0, l;
	int flag[150]={0};
	l = strlen(s);
	
	for(i=0; i<l; i++)//j用来看s的最终版输入 
	{
		if(flag[s[i] - 32] == 0)
		{
			s[j++] = s[i];
			flag[s[i] - 32] = 1;
		}
	}
	//补全 
	for(i = 0; i < 95; i++)
	{
		if(flag[i]==0)
			s[j++] = 32 + i;	
	}
	//puts(s);
}
