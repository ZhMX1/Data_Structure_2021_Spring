#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define  MAXSIZE 200  //�������� 
#define THRESHOLD  7  //����������ֵ�������� 
#define MAXSVR  5   //�����񴰿���
#define MINSVR  3    //��С���񴰿���
typedef struct {
    int id;
    int wtime;
}CustType;

int Winnum = MINSVR; //�ṩ����Ĵ�����
int front = 0, rear = MAXSIZE-1, count = 0;
CustType queue[MAXSIZE];
 
void updateCustqueue(); //���µȴ������пͻ��ȴ�ʱ��
void enCustqueue(CustType c); //�ͻ���ȴ����� 
CustType deCustqueue(); //�ͻ�����
int getCustnum();   //��ȡ���еȴ��ͻ�����
int isFull();
int isEmpty();
void arriveCust();	//��ȡ�¿ͻ����������ȴ�������
int service();	//���дӶ����л�ȡ�ͻ����з���

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
            break;  //�ȴ�����Ϊ���Ҳ������¿ͻ�
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
    while((getCustnum() / Winnum) >= THRESHOLD && Winnum<MAXSVR)  //���ӷ��񴰿�
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


