#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define  MAXSIZE 200  //队列容量 
#define THRESHOLD  7  //窗口增加阈值（人数） 
#define MAXSVR  5   //最大服务窗口数
#define MINSVR  3    //最小服务窗口数
typedef struct {
    int id;
    int wtime;
}CustType;

int Winnum = MINSVR; //提供服务的窗口数
int front = 0, rear = MAXSIZE-1, count = 0;
CustType queue[MAXSIZE];
 
void updateCustqueue(); //更新等待队列中客户等待时间
void enCustqueue(CustType c); //客户入等待队列 
CustType deCustqueue(); //客户出队
int getCustnum();   //获取队中等待客户人数
int isFull();
int isEmpty();
void arriveCust();	//获取新客户，并加至等待队列中
int service();	//银行从队列中获取客户进行服务

int main()
{
	int clock, simulationtime;
    scanf("%d", &simulationtime);
    for(clock=1; ; clock++) 
	{
        updateCustqueue();
        if(clock <= simulationtime )
            arriveCust();  
        if(service() == 0 && clock > simulationtime)
            break;  //等待队列为空且不会有新客户
    }
    return 0;
}

void arriveCust(){
    int i, n;
    CustType c;
    static idCount = 1;
    scanf("%d" , &n);
    for(i=0; i<n; i++)
	{
        c.id = idCount++; 
		c.wtime = 0;
        enCustqueue(c);
    }
    while((getCustnum() / Winnum) >= THRESHOLD && Winnum<MAXSVR)  //增加服务窗口
        Winnum++;
}

int service(){
    int i;
    CustType c;
    for(i=0; i<Winnum; i++)
    {
        if(isEmpty()) return 0;
		else
		{
			c = deCustqueue();
			printf("%d : %d\n" , c.id, c.wtime);
	    }
	} 
    if((getCustnum() / Winnum) < THRESHOLD && Winnum > MINSVR)
        Winnum--;
    return 1;
} 

void updateCustqueue(){
	int i;
	if(rear < front)
	{
		for(i = 0; i<rear; i++)
			queue[i].wtime++;
		for(i = front; i<MAXSIZE; i++)
			queue[i].wtime++;
	}
	else
		for(i = front; i<=rear; i++)
			queue[i].wtime++;
}

void enCustqueue(CustType c){
	if(isFull()){
		printf("ERROR_FULL");
	}
	else{
		rear = (rear+1) % MAXSIZE; 
		queue[rear] = c; 
		count++;
	}
}

CustType deCustqueue(){
	CustType elem;
	if(isEmpty()){
		printf("ERROR_EMPTY");
	}
	else{
		elem = queue[front];
	    front = (front+1) % MAXSIZE;
	    count--;
	    return elem;
	}
}

int isEmpty(){
	return count == 0;
}

int isFull(){
	return count == MAXSIZE;
}

int getCustnum(){
	return count;
}


