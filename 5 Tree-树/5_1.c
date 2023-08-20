#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct node{
    int num;
    int high;//计算树高 
    struct node *left, *right;
};
typedef struct node BTNode;
typedef struct node *BTNodeptr;
BTNodeptr createTree( BTNodeptr root , int data);
void inorder(BTNodeptr t);
int cnt = 0;
int main()
{
	int n = 0;
	scanf("%d", &n);
	BTNodeptr tree = NULL;
	
	int a = 0;
	int i = 0;
	for(i = 0; i<n ;i++)
	{
		cnt = 0;
		scanf("%d", &a);
		tree = createTree( tree , a );
	}
	
	inorder( tree );
	return 0;
}

BTNodeptr createTree( BTNodeptr root , int data)
{
	BTNodeptr q;
	cnt++;
	if(root == NULL)//空节点插入 
	{
		q = (BTNodeptr)malloc(sizeof(struct node));
		q->num = data;
		q->high = cnt;
		q->left = NULL;
		q->right = NULL;
		root = q ;
	}
		
	else if(data < root->num) 
	{			
		root->left = createTree( root->left , data);
	}
	else if(data >= root->num) 
	{			
		root->right = createTree( root->right , data);
	}
	return root;
}

void inorder(BTNodeptr t)//中序遍历 
{
    if(t!=NULL){
	    inorder(t->left);
        //VISIT(T);       /* 访问T指结点  */
        if(t->left == NULL && t->right == NULL)
        	printf("%d %d\n", t->num, t->high);
        inorder(t->right);
       }
}

