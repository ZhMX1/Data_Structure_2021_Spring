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
    //�ų�key������ظ��ַ� 
    int j=0;//�����γ����յĶ��չ�ϵ 
    int flag[50]={0};//��key����û�����е���ĸ 
	for(i=0; i<l; i++)
	{
		if(flag[key[i]-'a']==0)
		{
			key[j++] = key[i];
			flag[key[i]-'a']=1;
		}	
	}
	//��ʣ�µ���ĸ���ε�������
	for(i=25; i>=0; i--)
	{
		if(flag[i]==0)
		key[j++]=i+'a';	
	} 
	//����
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


