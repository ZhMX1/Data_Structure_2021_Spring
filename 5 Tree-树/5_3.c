#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 510
struct link{
	char content[max];
	struct link *next;
}; 

struct node{
    char operate[max];
    struct node *left, *right;
};
typedef struct link *Nodeptr;
typedef struct node *BTNodeptr;

int pri(char a);
int cmpPri(char a, char b);
int operate(char a, int p, int q);
void clearStr(char word[]);
void createLink(char word[] , int n);
int changeNum(char numWord[]);
void popStack(char op[] , char a);
BTNodeptr createTree( BTNodeptr stack[] , Nodeptr cur);
void getAnswer();

Nodeptr list = NULL , end = NULL;
int top = 0, j = 0;
int main()
{
	Nodeptr cur;
	BTNodeptr tree = NULL, stack[max] ;
	
	char infix[max] = {'\0'};
	gets(infix);
	int len = strlen(infix);
	
	//��ͨ��������һ����׺���ʽ��ȫ�������ַ�����ʾ
	//��ͨ��������׺���ʽ����һ����
	char numWord[max] = {'\0'}; 
	char op[max] = {'\0'};//����ջ 
	int i = 0; 
	for(i = 0; i<len ; i++)
	{
		if( infix[i]>='0' && infix[i]<='9')//�ж�����
			numWord[j++] = infix[i]; 
		
		else if(infix[i] == ' ' )
		{
			createLink(numWord , j);
			clearStr(numWord);//ע���ַ������� 
		}

		else if(infix[i] == '=' )
		{
			createLink(numWord , j);
			clearStr(numWord);
			popStack(op , infix[i]);
		}
		
		else//�Ƿ��� 
		{
			createLink(numWord , j);
			clearStr(numWord);
			if(top == 0)
				op[++top] = infix[i];
			
			else if(cmpPri(infix[i], op[top]) == 1)//���ȼ��� 
			{
				if(infix[i] != ')')//���������Ž�ջ 
					op[++top] = infix[i];
				else//�������ų�ջ�������� 
					popStack(op , infix[i]);
			}
			
			else if(cmpPri(infix[i], op[top]) == 0)//���ȼ��͡�һ�� 
			{
				if(op[top] == '(')//ջ���������ţ�������ջ 
					op[++top] = infix[i];
				else//ջ�����������ţ�������ƽ�� 
				{
					popStack(op , infix[i]);
					op[++top] = infix[i];
				}	
			}
		}
	}
//	for(cur = list; cur!=NULL; cur = cur->next) 
//		printf("%s\n", cur->content);
		
	cur = list;
	tree = createTree( stack , cur );
	printf("%c %c %c\n", tree->operate[0], tree->left->operate[0], tree->right->operate[0]);
	
	getAnswer();
	return 0;
}

void createLink(char word[] , int n){
	if(n != 0)
	{
		Nodeptr q;
		q = (Nodeptr)malloc(sizeof(struct link));
		strcpy(q->content , word);
		q->next = NULL;
		
		if(list == NULL)
			list = q;
		else 
			end->next = q;
		end = q;
	}
	j = 0; 
}

void popStack(char op[] , char a){
	char opWord[max] = {'\0'};
	if(a == ')')
	{
		while(op[top] != '(')
		{
			opWord[0] = op[top];
			createLink(opWord , 1);
			top--;
		}
		op[top] = '\0';
		top--;//�������ŵ��� 
	}
	else 
	{
		while(cmpPri(a, op[top]) == 0 && top>0)
		{
			if(op[top] == '(')
			{
				break;
			}	
			else
			{
				opWord[0] = op[top];
				createLink(opWord , 1);
				top--;
			}		
		}
	}
}

int changeNum(char numWord[]){
	int num = 0;
	int n = strlen(numWord);
	int i;
	for(i = 0; i < n; i++)
		num = num*10 + numWord[i] - '0';
	return num;
}

BTNodeptr createTree( BTNodeptr stack[] , Nodeptr cur){
	BTNodeptr q;
	static cnt = 0; 
	for(; cur!=NULL; cur = cur->next) 
	{
		q = (BTNodeptr)malloc(sizeof(struct node));
		strcpy(q->operate , cur->content);
		q->left = q->right = NULL;
	
		if(q->operate[0] >= '0' && q->operate[0] <= '9')//������
		{
			stack[cnt++] = q; 
		} 
		else//�������
		{
			q->left = stack[cnt-2];
			q->right = stack[cnt-1];
			stack[cnt-1] = NULL;
			stack[cnt-2] = q;
			cnt--;
		} 
	}
	return stack[0];
}

void getAnswer(){
	int cal[max] = {0};
	int i = 0;
	while(list != NULL)
	{
		if(list->content[0]>='0' && list->content[0]<='9')
			cal[i++] = changeNum(list->content);
		else
		{
			cal[i-2] = operate(list->content[0], cal[i-2], cal[i-1]);
			cal[i-1] = 0;
			i--;
		}
		list = list->next;
	}
	printf("%d", cal[0]);
}

void clearStr(char word[]){
	int n = strlen(word);
	int i = 0;
	for(i = 0; i<n; i++)
		word[i] = '\0'; 
}

int pri(char a){
	if(a == '(' || a == ')')
		return 2;
	if(a == '*' || a == '/' || a == '%')
		return 1;
	if(a == '+' || a == '-' || a == '=')
		return 0;
}

int cmpPri(char a, char b){
	if(pri(a) <= pri(b))
		return 0;
	else	return 1;
}

int operate(char a, int p, int q){
	if(a == '+') return p+q;
	else if(a == '-') return p-q;
	else if(a == '*') return p*q;
	else if(a == '/') return p/q;
	else if(a == '%') return p%q; 
}

