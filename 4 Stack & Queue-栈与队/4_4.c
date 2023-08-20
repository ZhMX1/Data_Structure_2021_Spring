#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 550
typedef struct link{
	int op;
	int pos;
	char str[max];
	struct link *right, *left;
}*Nodeptr;

Nodeptr head = NULL, end;
void createList(int n);
void insertNode(int operate);
void insertStr(char line[], int len);
void deleteStr(char line[], int len);

int main()
{
	char line[max] = {'\0'};
	gets(line);
	int len = 0;
	int n = 0;
	scanf("%d", &n);
	createList(n);

	int operate = 0;
	while(scanf("%d" , &operate))
	{
		if(operate == -1)
		{
			puts(line);
			break;
		}
		
		else if(operate == 1)//插入 
		{
			insertNode(operate);
			len = strlen(line);
			insertStr(line, len);
		}
		
		else if(operate == 2)//删除 
		{
			insertNode(operate);
			len = strlen(line);
			deleteStr(line, len);
		}
		
		else if(operate == 3)//撤销 
		{
			if(end == NULL)	continue;
			else if(end->op == 1)
			{
				len = strlen(line);
				deleteStr(line, len);
			}
			else
			{
				len = strlen(line);
				insertStr(line, len);
			}		
			end = end->left;
		}
	}
	return 0;
}

void createList(n){
	Nodeptr  p = NULL, q, list = NULL;
	int i = 0;
	for(i=0; i<n; i++)
	{
		int num1 = 0, num2 = 0;
		char string[max] = {'\0'};
		scanf("%d%d%s", &num1, &num2, string);
		
		q = (Nodeptr)malloc(sizeof(struct link));
		q->op = num1;
		q->pos = num2;
		strcpy(q->str , string);
		q->right = NULL;
		q->left = NULL;
			          
		if (list == NULL) 	/*链表为空*/
		{
			list = q;
			p = q;
		}
		
		else
		{
			p->right = q;
			q->left = p;
			p = q;
		}
	}
	end = p;
	head = list;
}

void insertNode(int operate){
	int num2 = 0;
	char string[max] = {'\0'};
	scanf("%d%s", &num2, string);
	
	Nodeptr q;	
	q = (Nodeptr)malloc(sizeof(struct link));
	q->op = operate;
	q->pos = num2;
	strcpy(q->str , string);
	
	if(head == NULL)//防止前方无操作 
	{
		q->right = q->left = NULL; 
		head = end = q;
	}
	else
	{
		q->right = NULL;
		q->left = end;
		end->right = q; 
		end = q;
	} 	
}

void insertStr(char line[], int len){
	int n = end->pos;
	int i = 0, j = 0;
	int l = strlen(end->str);
	char lineCpy[max] = {'\0'};
	for(i=0; i<n; i++)
		lineCpy[j++] = line[i];
	for(i=0; i<l; i++)
		lineCpy[j++] = end->str[i];
	for(i=n; i<len; i++)
		lineCpy[j++] = line[i];
	strcpy(line, lineCpy);
		
}

void deleteStr(char line[], int len){
	int num = changeNum(end->str);//要删除的个数 
	int p = end->pos;
	int i = 0, j = 0, k = 0;
	
	if(end->op == 1)//专门给撤销的 
	{
		num = 0; 
		for(i = 0; end->str[i]!= '\0';i++)
			num++; 
	}
	
	for(i=0; i<p ; i++)
		line[j++] = line[i];
	for( ; i<p+num; i++)
		end->str[k++] = line[i];//记录删掉的字符 
	for( ; i<len; i++)
		line[j++] = line[i];
	for(; j<len; j++)
		line[j] = '\0';//删除后清零 
}

int changeNum(char numWord[]){
	int num = 0;
	int n = strlen(numWord);
	int i, j, mid = 0;
	for(i = 0; i < n; i++)
	{
		mid = numWord[i] - '0';
		for(j = 0; j < n-i-1; j++)
			mid *= 10;
		num += mid;
	}
	return num;
}

/*int changeNum(char ch[]){
	int a, s = 0;
	for (a = 0; ch[a] >= '0' && ch[a] <= '9'; a++)
	    s = 10 * s + ch[a] - '0';
	return s;
}*/


