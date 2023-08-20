#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 1024

struct list{
	int n;//行数 
	char c;
}stack[250], record[250]; 

int lineNum = 0;//记录行号 
int top = 0;//stack	
int cnt = 0;//record
//注意cnt和top计数是从0/1开始的 
int flag = 0;
void popStack( struct list stack[] ,char line[] ,int i );
int skip( FILE *fp , int i , char line[]);

char line[max] = {'\0'};
int main()
{
	FILE *fp = fopen("example.c","r");
	int i = 0;
	
	while(fgets(line, max, fp))
	{
		lineNum++;
		int len = strlen(line);
		
		for(i = 0; i < len; i++)
		{
			if(line[i] == '/' || line[i] == '\"' )
				i = skip( fp , i, line );//skip进来有两种可能：字符串/注释，分类讨论 
			if(i>=len)	break;
			if(line[i] == '{' || line[i] == '(' ){
				top++;
				stack[top].n = lineNum;
				stack[top].c = line[i];
				
				cnt++;
				record[cnt].n = lineNum;
				record[cnt].c = line[i];
				
			if(line[i] == '{' && top>=2 && stack[top-1].c == '(' && flag == 0)
				{
					printf("without maching \'%c\' at line %d", stack[top-1].c, stack[top-1].n);
					flag = 1;
				}
				//printf("%c   %d\n", record[cnt].c, record[cnt].n);
			}

			else if(line[i] == '}' || line[i] == ')' ){
				cnt++;
				record[cnt].n = lineNum;
				record[cnt].c = line[i];
				//printf("%c   %d\n", record[cnt].c, record[cnt].n);
				popStack( stack , line , i);//仅判断右侧不匹配 
			}
		}
	}
	
	if(top != 0 && flag == 0)//左侧不匹配 
		printf("without maching \'%c\' at line %d", stack[top].c, stack[top].n);

	else if(flag == 0)
		for( i=1; i<=cnt; i++) 
			printf( "%c", record[i].c );
	
	fclose(fp);
	return 0;
}

void popStack( struct list stack[], char line[], int i){
	if(top == 0 && flag == 0)
	{
		printf("without maching \'%c\' at line %d", record[cnt].c, record[cnt].n);
		flag = 1;
	}
	else if(line[i] == ')' && stack[top].c !='(' && flag == 0)
	{
		printf("without maching \'%c\' at line %d", record[cnt].c, record[cnt].n);
		flag = 1;
	}
	else if(line[i] == '}' && stack[top].c !='{' && flag == 0)
	{
		printf("without maching \'%c\' at line %d", record[cnt].c, record[cnt].n);
		flag = 1;
	}
	else if((line[i] == ')' && stack[top].c =='(')||(line[i] == '}' &&stack[top].c =='{'))
		top--;
	
}

int skip( FILE *fp , int i , char line[]){
	int len = strlen(line);
	
	if(line[i] == '/' ) 
	{
		if(line[i+1] == '/')
			return max;
		
		else if(line[i+1] == '*')
		{
			for(i=i+2; i<len; i++)
				if(line[i] == '*' &&line[i+1] == '/')
					return i+2;

			while(fgets(line, max, fp))
			{	
				lineNum++;
				int len = strlen(line);
				for(i=0; i<len; i++)
					if(line[i] == '*' &&line[i+1] == '/')
						return i+2;	
			}	
		}
	} 
	
	
	else if(line[i] == '\"')
	{
		for(i=i+1; i<len; i++)
		{
			if(line[i] == '\"')
				return i+1;
		}
	}
}


