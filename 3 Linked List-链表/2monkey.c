#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct link{
	int num;
	struct link *next;
}; 
int main()
{
	int n, m, Q;
	scanf("%d%d%d", &n, &m, &Q);
	int i;
	struct link *head=NULL, *p,*q;
	for(i=0; i<n; i++)
	{
		q=(struct link *)malloc(sizeof(struct link));
		q->num = i+1;
		q->next = NULL;//开新的储存空间 

		if(head == NULL)
			head = p = q;
		else{
			p->next = q;
			p = p->next;
		}
	}
	p->next = head;
	p = head;//建了一个循环链表 
	
	int cnt = 0;//记录删掉几只猴子 
	int num = 1;//记录报号 
	for(i=0; i<Q+n-2; i++)//p已经在第一个上面了，所以-2 
		p = p->next;//p指到第Q个猴子前一个开始报数
//从1开始报数的情况需要处理一下 就是让指针多转一圈，然后指向n 
	while(cnt<n-1) 
	{
		if(num != m)
		{
			p = p->next;//指向该报此时num的猴子 
			num++;//下一个猴子该报的数 
		}
		else
		{	
			q = p->next;
			p->next = p->next->next;
			free(q);
			cnt++; 
			num = 1;
		}
	}
	printf("%d", p->num);

	return 0;
}


