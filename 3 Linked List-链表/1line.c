#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
int x_0;
int y_0;
int x, y;
int num1, num2, num;
struct list{
	int x1;
	int y1;
	int x2;
	int y2;
}; 
int checkback(struct list line[], int i, int n);
int checkforward(struct list line[], int i, int n);
int main()
{
	struct list line[150];
	int n, i, j;
	
	scanf("%d", &n);
	for(i=0; i<n; i++)
		scanf("%d%d%d%d", &line[i].x1, &line[i].y1, &line[i].x2, &line[i].y2);

	int cnt=1, cntmax=0;
	//先向后查找 尾==头 改变线段数量 
	//再向前查找 头==尾	改变起点位置和线段数量 
	for (i=0; i<n; i++)
	{
		num = 0;
		num1 = checkback(line, i, n);
		num = 0;
		num2 = checkforward(line, i, n);
		cnt = cnt + num1 + num2;
		if(cnt>cntmax)
		{
			cntmax = cnt;
			x = x_0;
			y = y_0; 
		}
		cnt=1; 
	}
	printf("%d %d %d", cntmax, x, y);
	return 0;
}

int checkback(struct list line[], int i, int n){
	int j;
	for(j=0; j<n; j++)
		if(line[i].x2 == line[j].x1 && line[i].y2 == line[j].y1)
		{
			num++;
			checkback(line, j, n);		
		}
	return (num);		
}

int checkforward(struct list line[], int i, int n){
	int j;
	x_0 = line[i].x1;
	y_0 = line[i].y1;
	for(j=0; j<n; j++)//线段排序问题，所以需要从头循环 
		if(line[i].x1 == line[j].x2 && line[i].y1 == line[j].y2)
		{
			num++;
			x_0 = line[j].x1;
			y_0 = line[j].y1;
			checkforward(line, j, n);		
		}
	return (num);		
}


