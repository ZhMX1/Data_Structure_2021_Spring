#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 1024
void changeNum(int numWord[], int num[], int n); 
int pri(char a);
int cmpPri(char a, char b);
int operate(char a, int p, int q);
void popStack(char op[], int num[], char a);
void getAnswer(int num[],char op[]);

int top = 0, cnt = 0, j = 0;
int main()
{
	char infix[max] = {'\0'};
	gets(infix);//������ô���룬��Ϊ���ܻ���ֶ�λ���� 
	int len = strlen(infix);
	
	char op[max] = {'\0'};//����ջ 
	int num[max] = {0};//����ջ 
	int numWord[max] = {0};
	int i = 0;
	
	for(i = 0; i<len ; i++)
	{
		if( infix[i]>='0' && infix[i]<='9')
			numWord[j++] = infix[i] - '0';
		
		else if(infix[i] == ' ' )
			changeNum(numWord, num, j); 

		else if(infix[i] == '=' )
		{
			changeNum(numWord, num, j); 
			getAnswer(num, op);
		}
		
		else
		{
			changeNum(numWord, num, j); 
			if(top == 0)
				op[++top] = infix[i];
			
			else if(cmpPri(infix[i], op[top]) == 1)//���ȼ��� 
			{
				if(infix[i] != ')')//���������Ž�ջ 
					op[++top] = infix[i];
				else//�������ų�ջ�������� 
					popStack(op , num, infix[i]);
			}
			
			else if(cmpPri(infix[i], op[top]) == 0)//���ȼ��͡�һ�� 
			{
				if(op[top] == '(')//ջ���������ţ�������ջ 
					op[++top] = infix[i];
				else//ջ�����������ţ�������ƽ�� 
				{
					popStack(op, num, infix[i]);
					op[++top] = infix[i];
				}	
			}
			
		}
	}

	return 0;
}

void changeNum(int numWord[], int num[], int n){
	if(n != 0)
	{
		cnt++; 
		int i, p;
		for(i = 0; i < n; i++)
		{
			for(p = 0; p < n-i-1; p++)
			{
				numWord[i] *= 10;
			}	
			num[cnt] += numWord[i];
		}
		j = 0;
	}
}

int pri(char a){
	if(a == '(' || a == ')')
		return 2;
	if(a == '*' || a == '/' || a == '%')
		return 1;
	if(a == '+' || a == '-')
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

void popStack(char op[], int num[], char a){
	if(a == ')')
	{
		while(op[top] != '(')
		{
			int mid = operate(op[top], num[cnt-1], num[cnt]);
			num[cnt-1] = mid;
			num[cnt] = 0;
			cnt--;
			top--;
		}
		top--;//�������ŵ��� 
	}
	else 
	{
		while(cmpPri(a, op[top]) == 0)
		{
			if(op[top] == '(')
			{
				break;
			}	
			else
			{
				int mid = operate(op[top], num[cnt-1], num[cnt]);
				num[cnt-1] = mid;
				num[cnt] = 0;
				cnt--;
				top--;
			}		
		}
	}
}

void getAnswer(int num[],char op[]){
	while(top != 0)
		{
			int mid = operate(op[top], num[cnt-1], num[cnt]);
			num[cnt-1] = mid;
			num[cnt] = 0;
			cnt--;
			top--;
		}
	printf("%d", num[cnt]);
}


