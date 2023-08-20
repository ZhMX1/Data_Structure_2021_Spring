#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int i, j, k, ;
	char m, s1[105], s2[105]={0};
	gets(s1);
	for(i=j=0; s1[i]!='\0'; i++)
	{
		if(s1[i]!='-')
			s2[j++] = s1[i];
		else
		{
			n = s1[i+1] - s1[i-1] - 1;
			if(s1[i-1]>='a' && s1[i+1]<='z')
				for(k=1; k<=n; k++) s2[j++] = s1[i-1]+k;	
			else if( s1[i-1]>='A' && s1[i+1]<='Z')
				for(k=1; k<=n; k++) s2[j++] = s1[i-1]+k;
			else if(s1[i-1]>='0' && s1[i+1]<='9')
				for(k=1; k<=n; k++) s2[j++] = s1[i-1]+k;
			else
				s2[j++] = s1[i];
		}
	}
	s2[j]='\0';
	puts(s2);
	
	return 0;
}

