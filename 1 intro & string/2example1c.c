#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int a1, a2, a3, sum=0;
	char f1, f2, f3;
	//scanf("%d %c", &a1, &f1);
	a1=0;
	f1='+'; //��ʼ�� 
	//�üӼ����Ű�������ʽ��Ϊ�������֣���Ԫ�� 
	//���ѭ���жϼӼ����Ե�Ԫ�����ڲ�ѭ�����㵥Ԫ�ڲ��˳� 
	while(f1!='=')
	{
		//scanf("%d %c", &a2, &f2);
		scanf("%d %c", &a2, &f2);
		while(f2=='*'||f2=='/')	
		{
			scanf("%d %c", &a3, &f3);
			if(f2=='*')
				a2 *= a3;
			else if(f2=='/')
				a2 /= a3;
			f2 = f3;
		}//�ж�һ�����˳��Ĳ��� 
	
		if(f1 == '+')
			sum += a2;
		else if(f1 == '-')
			sum -= a2;
		f1 = f2;
	}	
	printf("%d", sum);
	//if(f1=='=') printf("%d", sum);	

	return 0;
}


