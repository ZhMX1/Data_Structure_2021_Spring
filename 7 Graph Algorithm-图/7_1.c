#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 105
int graph[max][max]; 
int visited[max]; 

void DFS(int vertex, int point);
void BFS(int vertex, int point);
void initialQueue();
void enqueue(int a);
int dequeue();
int main()
{
	memset(graph, 0, sizeof(graph));
	int vertex=0, edge=0;
	scanf("%d%d", &vertex, &edge);
	int i=0, s=0, t=0;
	for(i=0; i<edge; i++)
	{
		scanf("%d%d", &s, &t);
		graph[s][t] = 1;
		graph[t][s] = 1;
	}
	int deleteVertex = 0;
	scanf("%d", &deleteVertex);
	
	memset(visited, 0, sizeof(visited));
	DFS(vertex, 0);
	printf("\n"); 
	
	memset(visited, 0, sizeof(visited));
	BFS(vertex, 0);
	printf("\n"); 
	
	for(i=0; i<edge; i++)//将要删除结点的边标记为0，删掉
	{
        graph[deleteVertex][i] = 0;
        graph[i][deleteVertex] = 0;
    }
    
	memset(visited, 0, sizeof(visited));
    DFS(vertex, 0);
	printf("\n"); 
	
	memset(visited, 0, sizeof(visited));
	BFS(vertex, 0);
	printf("\n"); 
	return 0;
}

void DFS(int vertex, int point){//深度优先遍历 
	visited[point] = 1;
	printf("%d ", point);
	int i = 0; 
	for(i=0; i<vertex; i++){
		if(graph[point][i]!=0 && visited[i]==0) 
			DFS(vertex, i);
	}
}

int queue[max];
int front, rear, cnt;
void BFS(int vertex, int point){//广度优先遍历 
	initialQueue(); 
	int temp = 0, i = 0;
	enqueue(point);
	while(cnt != 0)
	{
		temp = dequeue();
		printf("%d ", temp);
		for(i=0; i<vertex; i++)
			if(graph[temp][i]!=0 && visited[i]==0)
				enqueue(i);
	}
}
void initialQueue(){
	front = 0;
	rear = max-1;
	cnt = 0;
	memset(queue, -1, sizeof(queue));	
}
void enqueue(int a){
	visited[a] = 1;
	rear = (rear+1)%max;
	queue[rear] = a;
	cnt++;
}
int dequeue(){
	int temp = 0;
	temp = queue[front];
	front = (front+1)%max;
	cnt--;
	return temp;
}

