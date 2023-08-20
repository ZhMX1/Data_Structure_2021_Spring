#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 10010
//��ɾ�Ĳ� 
typedef struct link{
	char word[50];
	int num;
	struct link *next;
}*Nodeptr;

int scan(FILE *file , char word[]);
Nodeptr createList( FILE *file );	//����һ���� 
//void uni_zifu(char s[]);
Nodeptr insertFirst( Nodeptr list, Nodeptr q );
Nodeptr insertNode( Nodeptr list, Nodeptr q );
void printList(Nodeptr list);	//���һ����

int main()
{
	Nodeptr list = NULL, p, q;
	FILE *fp = fopen("article.txt","r");

	list = createList( fp );
	printList( list );
	fclose( fp );
	return 0;
}

Nodeptr createList( FILE *file )  /*����һ������ */
{
    Nodeptr  p, q, list = NULL;
	char word[50] = {'\0'}; 
	char c = fgetc(file);
	int i = 0;
	
    while(c != EOF)
	{
		if(isalpha(c))
		{
			c = tolower(c);
			word[i++] = c;
		}
		else
		{
			if(i != 0)
			{
				//uni_zifu(word);
				q = (Nodeptr)malloc(sizeof(struct link));
		        strcpy(q->word , word);
				q->num = 1;//ע���ʼֵ������ 
		        q->next = NULL;
		          
			    if (list == NULL) 	/*����Ϊ��*/
		        	list = p = q;	//��һ���ڵ� //���Ա��list->next =q 
		    	else
					list = insertNode( list , q );  
			}
			int j;
			for(j=0; j<i; j++)
				word[j] = '\0';
			i = 0;
		}
        c = fgetc(file);
    }
    return list;
}

Nodeptr insertNode( Nodeptr list , Nodeptr q)
{
	Nodeptr  p = list; 
	if(strcmp(q->word, list->word) < 0)
	{//ͷ����
		list = insertFirst(list , q ); //����ͷ�ڵ����Ҫ�ı�ͷָ���ַ 
	}

	else
	{
		for(p = list; p->next != NULL; p = p->next)
		{
			if( strcmp(q->word, p->word) == 0 )//�ظ����� 
			{
				p->num++;
				break;
			}
			else if(strcmp(q->word, p->word)>0 && strcmp(q->word, p->next->word)<0)  
			{//�ҵ�һ�����λ�ã��м���� 
				q->next = p->next;		
				p->next = q; 
				break;
			} 	
		}
	}
	if(p->next == NULL)
	{
		if(strcmp(q->word, p->word) == 0)
			p->num++;//�ٴ��ж��ظ����� 
		else
			p->next = q;//β���� 
	}
	return list;//��Ҫ�����µ�ͷ�ڵ�λ�ã�Ҫô����list->next=q 
}

Nodeptr insertFirst( Nodeptr list, Nodeptr q )
{
	q->next = list;
	return q;
}

void printList(Nodeptr list)
{
	Nodeptr p = list;
	while(p != NULL)
	{
		printf("%s %d\n", p->word, p->num);
		p = p->next;
	}
} 

/*void uni_zifu(char s[])
{
	int len;
	int i, j;
	len = strlen(s);
	for(i = j = 0; i < len; i++)
	{
		if(isalpha(s[i]))
		{
			s[i] = tolower(s[i]);
			s[j++] = s[i];
		}
	}
		
	while( j < len)
		s[j++] = '\0'; //������ɾ�����ظ����ַ��ĺ���Ҫ���� 
}*/



