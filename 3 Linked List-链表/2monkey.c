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
		q->next = NULL;//���µĴ���ռ� 

		if(head == NULL)
			head = p = q;
		else{
			p->next = q;
			p = p->next;
		}
	}
	p->next = head;
	p = head;//����һ��ѭ������ 
	
	int cnt = 0;//��¼ɾ����ֻ���� 
	int num = 1;//��¼���� 
	for(i=0; i<Q+n-2; i++)//p�Ѿ��ڵ�һ�������ˣ�����-2 
		p = p->next;//pָ����Q������ǰһ����ʼ����
//��1��ʼ�����������Ҫ����һ�� ������ָ���תһȦ��Ȼ��ָ��n 
	while(cnt<n-1) 
	{
		if(num != m)
		{
			p = p->next;//ָ��ñ���ʱnum�ĺ��� 
			num++;//��һ�����Ӹñ����� 
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


