#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct link{
	int xishu;
	int zhishu;
	struct link *next;
}; 
int main()
{
	struct link *head=NULL, *p, *q, *min, *max;
	int a[10005][5], b[10005][5];
	int i=0, j=0, n1=0, n2=0;
	
	char c = '\0';
	while(c!='\n')
	{
		scanf("%d%d", &a[i][0], &a[i][1]);
		n1++;
		i++;
		c = getchar();
	}
		
	c = '\0';
	i = 0;
	
	while(c!='\n')
	{
		scanf("%d%d", &b[i][0], &b[i][1]);
		n2++;
		i++;
		c = getchar();
	}
	
	int n=0;
	//��¼��һЩ�����ٽ��в��� 
	for(j=0; j<n2; j++)//q���½ṹ�壬p�Ǿɽṹ�� 
		{
			q=(struct link *)malloc(sizeof(struct link));
			q->xishu = a[0][0] * b[j][0];
			q->zhishu = a[0][1] + b[j][1];
			q->next = NULL;
			n++;
			if(head == NULL)
				head = p = q;//head�϶������� 
			else
			{
				p->next = q;
				p = p->next;
			}
		}
	
	for(i=1; i<n1; i++)
	{
		max = head;
		min = max->next;//һǰһ����� 
		for(j=0; j<n2; j++)
		{
			q=(struct link *)malloc(sizeof(struct link));
			q->xishu = a[i][0] * b[j][0];
			q->zhishu = a[i][1] + b[j][1];
			q->next = NULL;//q��һ���µĽṹ�� 
			//n++;
			while(max->next != NULL)
			{
				if(q->zhishu < min->zhishu) 
				{
					if(min->next == NULL){//ע�������������ָ���Ƶ����һλ 
						min->next = q;
						break;
					}
					else{
						max = max->next;
						min = min->next;
					}
				}
				else if(q->zhishu == min->zhishu)
				{
					min->xishu += q->xishu;
					break;
				}
				else
				{
					max->next = q;
					q->next = min;
					max = q;
					break;
				} 
			}
		}
	}
//	printf("%d %d %d\n", n1, n2, n);
	for(p = head; p != NULL; p = p->next)
		printf("%d %d ", p->xishu, p->zhishu);
		
	
	return 0;
}


