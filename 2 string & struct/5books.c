#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h> 
#include<string.h>
struct list{
	char name[51];
	char author[21];
	char publish[31];
	char date[11];
};//实现题干对齐方式必须要特定的数组长度 
int main()
{
	struct list list[500];
	FILE *fp1, *fp2;
	int n=0, i, j;
	fp1 = fopen("books.txt","r");
	fp2 = fopen("ordered.txt","w");
	while(fscanf(fp1, "%s%s%s%s", list[n].name, list[n].author, list[n].publish, list[n].date)==4)
		n++;
	//排序
	char namechange[60]={'\0'}, achange[30]={'\0'}, pchange[40]={'\0'}, datechange[20]={'\0'};
	for(i=0; i<n; i++)
		for(j=i+1; j<n; j++)
		{
			if(strcmp(list[i].name, list[j].name)>0)
			{
				strcpy(namechange,list[i].name);
				strcpy(list[i].name,list[j].name);
				strcpy(list[j].name,namechange);
				
				strcpy(achange,list[i].author);
				strcpy(list[i].author,list[j].author);
				strcpy(list[j].author,achange);
				
				strcpy(pchange,list[i].publish);
				strcpy(list[i].publish,list[j].publish);
				strcpy(list[j].publish,pchange);
				
				strcpy(datechange,list[i].date);
				strcpy(list[i].date,list[j].date);
				strcpy(list[j].date,datechange);
			}	
		}
	
	int a;//1录入 2查找 3删除 
	scanf("%d",&a);
	while(a!=0)
	{
		if(a==1)
		{
			scanf("%s%s%s%s", list[n].name, list[n].author, list[n].publish, list[n].date);
			n++;
			for(i=0; i<n; i++)
				for(j=i+1; j<n; j++)
				{
					if(strcmp(list[i].name, list[j].name)>0)
					{
						strcpy(namechange,list[i].name);
						strcpy(list[i].name,list[j].name);
						strcpy(list[j].name,namechange);
						
						strcpy(achange,list[i].author);
						strcpy(list[i].author,list[j].author);
						strcpy(list[j].author,achange);
						
						strcpy(pchange,list[i].publish);
						strcpy(list[i].publish,list[j].publish);
						strcpy(list[j].publish,pchange);
						
						strcpy(datechange,list[i].date);
						strcpy(list[i].date,list[j].date);
						strcpy(list[j].date,datechange);
					}	
				}
		}
		char s[60];
		
		if(a==2) 
		{
			scanf("%s", s);
			for(i=0; i<n; i++)
				if(strstr(list[i].name, s)!=0)
					printf("%-50s%-20s%-30s%-10s\n", list[i].name, list[i].author, list[i].publish, list[i].date);	
		}

		if(a==3)
		{	int k;
			scanf("%s", s);
			for(i=0; i<n; i++)
				if(strstr(list[i].name, s)!=0)
				{
					for(k=i; k<n; k++)
					list[k] = list[k+1];
					n--;//输出的时候因为少行了所以n需要减小，才能输出到正确的结尾 
					i--;//因为后面的行提到前面了，被提上来这一行没有被查找过，所以会漏掉
				}
	 	//i-- n--必须放在if的语句括号中，只有检查到了要删除的行才能i--和n-- 
		}
		scanf("%d", &a);
	}
	for(i=0; i<n; i++)
		fprintf(fp2,"%-50s%-20s%-30s%-10s\n",list[i].name,list[i].author,list[i].publish,list[i].date);
	
	fclose(fp1);
	fclose(fp2);
	return 0;
}

