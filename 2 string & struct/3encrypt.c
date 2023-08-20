#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE  1024
char key[100];
char encrypt[1024]; 

int main()
{
	int i, l;
    FILE *fp1 = fopen("encrypt.txt","r");
    FILE *fp2 = fopen("output.txt","w");
    
	gets(key);
    l=strlen(key);
    //排除key里面的重复字符 
    int j=0;//用作形成最终的对照关系 
    int flag[50]={0};//看key里有没有所有的字母 
	for(i=0; i<l; i++)
	{
		if(flag[key[i]-'a']==0)
		{
			key[j++] = key[i];
			flag[key[i]-'a']=1;
		}	
	}
	//将剩下的字母依次倒叙输入
	for(i=25; i>=0; i--)
	{
		if(flag[i]==0)
		key[j++]=i+'a';	
	} 
	//加密
	char line[MAXLINE]; 
	while(fgets(line, MAXLINE-1, fp1) != NULL)
	{
		for(i=0; line[i]!='\0'; i++)
		{
			if(isalpha(line[i]))
				encrypt[i]=key[line[i]-'a'];
			else 	
				encrypt[i]=line[i];
		}
		fputs(encrypt, fp2);
	} 
	
	fclose(fp1);
	fclose(fp2);

	return 0;
}


