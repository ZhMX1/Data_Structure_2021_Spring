#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct list{
	char name[50];
	char num[20];
	char cf[5]; //���鿪С�˻���� 
}list[150]; 
int main()
{
	int n, i, j;
	//�Ȱ����ж��������� 
	scanf("%d",&n);
	for (i=0; i<n; i++)
    {
        scanf("%s", list[i].name);
        scanf("%s", list[i].num);
        list[i].cf[0] = '_';
        list[i].cf[1] = '0';
	} 
	//�ж������ظ��������������Ƚ� 
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
		{
			if(strcmp(list[i].name, list[j].name)==0&&strcmp(list[i].num,list[j].num)!=0)
			{
				list[i].cf[1]++;
				strcat(list[j].name,list[i].cf);
			} 
			if(strcmp(list[i].name, list[j].name)==0&&strcmp(list[i].num,list[j].num)==0)
				list[j].name[0]='0';//���һ�£�name��һ��Ϊ0����� 
		}
	//�ȶ�������qsort����
	//ð������ 
	char namechange[30]={'\0'};
	char numchange[20]={'\0'};
	for(i=0; i<n-1; i++)
		for(j=i+1; j<n; j++)
		{
			if(strcmp(list[i].name, list[j].name)>0)
			{
				strcpy(namechange,list[i].name);
				strcpy(list[i].name,list[j].name);
				strcpy(list[j].name,namechange);
				
				strcpy(numchange,list[i].num);
				strcpy(list[i].num,list[j].num);
				strcpy(list[j].num,numchange);			
			} 
		} 
	//���
	for(i=0; i<n; i++)
	{
		if(list[i].name[0]!='0')
		printf("%s %s\n\n", list[i].name, list[i].num);
	}
	return 0;
}


