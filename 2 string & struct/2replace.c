#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define MAXLINE  1024
int ind(char s[], char t[], char key[]);
int main()
{
	FILE *IN;
	FILE *out;
	int flag[MAXLINE]={0}, i;
	char line[MAXLINE], s[100], key[100];
	gets(s);
	gets(key);
	IN=fopen("filein.txt","r");
	out=fopen("fileout.txt","w");

	while(fgets(line, MAXLINE-1, IN) != NULL)
	{
		//flag����������ޱ������
		int j, k, p, l1, l2, cnt=0, num=0;
		char lowerline[MAXLINE]={'\0'}, lowers[100]={'\0'};
		l1 = strlen(line);
		l2 = strlen(s); 
		//���������µ��ַ�����ԭ�ַ��������Сд 
		for(i=0; i<l1; i++)
			lowerline[i] = tolower(line[i]);
		for(i=0; i<l2; i++)
			lowers[i] = tolower(s[i]);
		for(i=0; i<l1;)//������һ�� 
		{
			for(j=i, k=0; k<l2;j++,k++)
			{
				if(lowerline[j]==lowers[k])	cnt++;
			}
			
			if(cnt==l2)	//�������ؼ���ʱ 
			{	
				for(p=0; p<i; p++)//�ж�key����ǰ������������δ������
					if(flag[p]==0)
					{
						fputc(line[p], out);
						flag[p]=1;
					}
				fputs(key, out);//ǰ�����ֶ���������key 
				for(p=i; p<i+l2; p++)
			 		flag[p]=1;
				i+=l2; 
			}
			
			else
				i++;
			cnt=0;
		}
		for(p=0; p<i; p++)//�ж�key����ǰ������������δ������
			if(flag[p]==0)
				fputc(line[p], out);			
		for(i=0; i<l1; i++)
			flag[i]=0; 
	}
    fclose(IN);
	fclose(out);
	return 0;
}
  

