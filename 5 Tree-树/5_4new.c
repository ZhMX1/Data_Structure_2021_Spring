#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 1024
//利用最近的公共祖先的深度
//计算机深度-公共祖先+打印机深度-公共祖先=路径 
struct node{
	int id;
	int type;//0表示交换机、1表示计算机、2表示打印机
	int parent;
	int port;
	int depth;

	struct node *child[10];
	struct node *father; 
}; 
typedef struct node *BTNodeptr;
BTNodeptr targetPtr;
//BTNodeptr priStack[max];//用指针记录所有打印机的位置
BTNodeptr priStack[max];//用指针记录打印机的前序遍历顺序 
int priCnt = 0;
int dist = 0;

BTNodeptr createTree(FILE *fp, BTNodeptr tree, int num, int target);
BTNodeptr findParent(BTNodeptr tree , int parent);
void initialQueue(); 
void enqueue(BTNodeptr node);
BTNodeptr dequeue(BTNodeptr queue[]);
void routeToRoot(BTNodeptr node, int route[]);
int findAncestor(int cptRoute[] , int priRoute[]);
void preorder(BTNodeptr tree);


int main()
{
	FILE *fp;
	int i = 0;
	fp = fopen("in.txt", "r");
	int equip = 0, target = 0;
	scanf("%d%d", &equip, &target);
	
	BTNodeptr tree = NULL;
	tree = createTree(fp , tree , equip , target);
    
	int cptRoute[max];
	int priRoute[max];
	memset(cptRoute, -1, sizeof(cptRoute));
	memset(priRoute, -1, sizeof(priRoute));
	routeToRoot(targetPtr, cptRoute);
	preorder( tree );//前序遍历，是打印机存入栈中
		
	int distMin = max, ancestor = 0, ancestorMin = 0;
	BTNodeptr priMin = NULL;
	for(i = 0; priStack[i] != NULL; i++)
	{
		memset(priRoute, -1, sizeof(priRoute));
		routeToRoot(priStack[i], priRoute);
		ancestor = findAncestor(cptRoute , priRoute);

		if(dist < distMin)
		{
			distMin = dist;
			ancestorMin = ancestor;
			priMin = priStack[i];
		}
	}
	
	printf("%d ", priMin->id);
	BTNodeptr p = targetPtr;
	int answer[max];
	memset(answer, -1, sizeof(answer));
	
	while(p->id != ancestorMin)
	{
		p = p->father;
		printf("%d ", p->id);
	} 
	
	p = priMin;
	int half = 0;
	while(p->id != ancestorMin)
	{
		p = p->father;
		answer[half++] = p->id;
	}
	for(i = half-2; i>=0; i--)
		printf("%d ", answer[i]);
	
	fclose(fp); 
	return 0;
}
 
BTNodeptr createTree(FILE *fp, BTNodeptr tree, int num, int target){
	BTNodeptr q, par = NULL;
	int priNum = 0; 
	while(num--)
	{
		//建立一个新的节点 
		q = (BTNodeptr)malloc(sizeof(struct node));
		fscanf(fp, "%d%d%d%d\n", &q->id, &q->type, &q->parent, &q->port);
		int i = 0;
		for(i = 0; i < 8; i++)
			q->child[i] = NULL;
		
		if(q->parent == -1)//根节点 
		{
			q->depth = 1;
			q->father = NULL;
			tree = q;
		}
		else//其他节点 
		{
			par = findParent(tree , q->parent);//找父节点 
			//printf("father %d \n", par->id);
			q->depth = par->depth + 1;
			q->father = par;
			par->child[q->port] = q;
			
			if(q->id == target) //是指定计算机,用一个指针记录位置 
				targetPtr = q;
			/*printf("%d %d %d %d\n", q->id, q->type, q->parent, q->port);
			printf("%d\n", num);*/
		}
	}
	return tree;
}

//循环队列把节点挨个找一遍，找到父节点 
BTNodeptr queue[max];
int front, rear, count;

BTNodeptr findParent(BTNodeptr tree , int parent){//广度优先遍历算法 
	initialQueue();
	enqueue(tree);
	BTNodeptr temp;
	int i = 0;
	while(count != 0)
	{
		temp = dequeue(queue);
		if(temp->id == parent)
		{
			return temp;
		}
		else
		{
			for(i = 0; i < 8; i++)
				if(temp->child[i]!=NULL)
					enqueue(temp->child[i]);
		}
	}
}

void initialQueue(){
	front = 0;
	rear = max-1;
	count = 0;
	int i = 0;
	for(i = 0; i<max; i++)
		queue[i] = NULL; 
}

void enqueue(BTNodeptr node){
	rear = (rear+1)%max;
	queue[rear] = node;
	count++;
}

BTNodeptr dequeue(BTNodeptr queue[]){
	BTNodeptr temp;
	temp = queue[front];
	front = (front+1)%max;
	count--;
	return temp;
}

void routeToRoot(BTNodeptr node, int route[]){
	int i = 0;
	while(node != NULL)//这里再看一下 
	{
		route[i++] = node->id;//先移动可能会出现空节点 
		node = node->father;
	}
}

int findAncestor(int cptRoute[] , int priRoute[]){
	int i, j;
	for(i = 0; cptRoute[i] != -1; i++)	
		for(j = 0; priRoute[j] != -1; j++)
			if(cptRoute[i] == priRoute[j])
			{
				dist = i+j;
				return cptRoute[i];
			}
}

void preorder(BTNodeptr node){
	BTNodeptr t = node;
	int i = 0; 
	
	if(t != NULL)
	{
		if(t->type == 2) 
			priStack[priCnt++] = t;//是打印机进打印机栈 
		for(i = 0; i < 8; i++)
		{
			if(t->child[i] != NULL)
			{
				preorder( t->child[i] );//找到子节点前进 
			}
		}
	}
}


