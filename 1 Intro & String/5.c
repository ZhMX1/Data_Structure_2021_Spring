#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int n;
int flag[11]={0};
int ans[11];

void print();
void func(int index, int n);

int main()
{
	scanf("%d", &n);
	func(0,n); 

	return 0;
}

void print(){
	for(int i=0; i<n; i++)
		printf("%d ", ans[i]);
	puts("");
}

void func(int index, int n){
	if(index==n){
		print();
		return; 
	}
	int i;//i��Ϊȫ�ֱ�����ʱ������׳����� 
	for(i=1; i<=n; i++)
	{
		if(flag[i]==0)
		{
			ans[index]=i;
			flag[i]=1;
			func(index+1,n);
			flag[i]=0;//������һ��֮��i�Ĵ�С��ʵû�б仯��Ȼ��i++�����´���һ������ 
			ans[index]=0;	
		}
	}
	return;
}
