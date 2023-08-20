#include<stdio.h>
int Xjudge(int a[25][25] , int x , int y , int flag)
{
	if(a[x][y+1] == a[x][y] && a[x][y+1] != -1)
	{
		flag ++;
		if(flag == 3)  
		{
			if(a[x][y+2] == 0 || a[x][y-3] == 0)
				return 1;
			else return 0;
		}
		else return Xjudge(a, x, y+1, flag);
	}
	else return 0;
}


int Yjudge(int a[25][25] , int x , int y , int flag)
{
	if(a[x+1][y] == a[x][y] && a[x+1][y] != -1)
	{
		flag ++;
		if(flag == 3)  
		{
			if(a[x+2][y] == 0 || a[x-3][y] == 0)
				return 1;
			else return 0 ;
		}
		else return Yjudge(a, x+1, y, flag);
	}
	else return 0;
}

int XYjudge(int a[25][25] , int x , int y , int flag)
{
	if(a[x+1][y+1] == a[x][y] && a[x+1][y+1] != -1)
	{
		flag ++;
		if(flag == 3)  
		{
			if(a[x+2][y+2] == 0 || a[x-3][y-3] == 0)
				return 1;
			else return 0 ;
		}
		else return XYjudge(a, x+1, y+1, flag);
	}
	else return 0;
}

int YXjudge(int a[25][25] , int x , int y , int flag)
{
	if(a[x+1][y-1] == a[x][y] && a[x+1][y-1] != -1)
	{
		flag ++;
		if(flag == 3)  
		{
			if(a[x+2][y-2] == 0 || a[x-3][y+3] == 0)
				return 1;
			else return 0 ;
		}
		else return YXjudge(a, x+1, y-1, flag);
	}
	else return 0;
}




int a[25][25] ;
int main()
{
	int i , j ;
		
	for(i = 0 ; i <= 24 ; ++i)
		for(j = 0 ; j <= 24 ; ++j)
			a[i][j] = -1 ;//³õÊ¼»¯ 
				
	for(i = 1 ; i <= 19 ; ++i)
		for(j = 1 ; j <= 19 ; ++j)
			scanf("%d", &a[i][j]);//ÊäÈë
				
	int flag = 0;
				
	for( i = 1 ; i<= 19 ; ++i)
	{
		for(j = 1 ; j <= 19 ; ++j)
		{
			if(a[i][j] == 1 || a[i][j] == 2)
			{
				int x=0 , y=0 , xy=0 , yx=0 ;
				x = Xjudge(a , i , j , 0);
				y = Yjudge(a , i , j , 0);
				xy = XYjudge(a , i , j , 0);
				yx = YXjudge(a , i , j , 0);
				
				
				if( x+y+xy+yx != 0 )
				{
					printf("%d:%d,%d\n", a[i][j], i, j);
					flag = 1;
					break;
				}			
			}
		} 
		if(flag == 1)	break;
	}
		
	if(flag == 0)	printf("No\n")	;
	
	return 0;	
		
}
