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
	
	//先通过链表建立一个后缀表达式，全部都用字符串表示
	//再通过遍历后缀表达式建立一棵树
	char numWord[max] = {'\0'}; 
	char op[max] = {'\0'};//符号栈 
	int i = 0; 
	for(i = 0; i<len ; i++)
	{
		if( infix[i]>='0' && infix[i]<='9')//判断数字
			numWord[j++] = infix[i]; 
		
		else if(infix[i] == ' ' )
		{
			createLink(numWord , j);
			clearStr(numWord);//注意字符串清零 
		}

		else if(infix[i] == '=' )
		{
			createLink(numWord , j);
			clearStr(numWord);
			popStack(op , infix[i]);
		}
		
		else//是符号 
		{
			createLink(numWord , j);
			clearStr(numWord);
			if(top == 0)
				op[++top] = infix[i];
			
			else if(cmpPri(infix[i], op[top]) == 1)//优先级高 
			{
				if(infix[i] != ')')//不是右括号进栈 
					op[++top] = infix[i];
				else//是右括号出栈到左括号 
					popStack(op , infix[i]);
			}
			
			else if(cmpPri(infix[i], op[top]) == 0)//优先级低、一样 
			{
				if(op[top] == '(')//栈顶是左括号，继续入栈 
					op[++top] = infix[i];
				else//栈顶不是左括号，弹出到平级 
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
		top--;//把左括号弹出 
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
	
		if(q->operate[0] >= '0' && q->operate[0] <= '9')//是数字
		{
			stack[cnt++] = q; 
		} 
		else//是运算符
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

