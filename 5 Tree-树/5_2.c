#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
struct node{
    char word[50];
    int cnt;//������ִ��� 
    struct node *left, *right;
};
typedef struct node *BTNodeptr;
int test = 0;
BTNodeptr createTree( FILE *file );
BTNodeptr insertNode( BTNodeptr root , char word[50]);
void inorderPrint(BTNodeptr t);

int main()
{
	BTNodeptr tree = NULL, p;
	FILE *fp = fopen("article.txt","r");

	tree = createTree( fp );
	
	int i = 0;
	p = tree;
	for(i = 0; i < 3 ; i++)
	{
		if(p != NULL)
			printf("%s ", p->word);
		else 
			break;
		p = p->right;
	}
	printf("\n");
	inorderPrint( tree );
	
	fclose( fp );
	return 0;
}

BTNodeptr createTree( FILE *file )
{
    BTNodeptr tree = NULL, q;
	char wordRead[50] = {'\0'}; 
	char c = fgetc(file);
	int i = 0;
	
    while(c != EOF)
	{	
		if(isalpha(c))
		{
			c = tolower(c);
			wordRead[i++] = c;
		}
		else
		{
			if(i != 0)
			{
				//printf("%s\n", wordRead);
				tree = insertNode(tree, wordRead); 
			}

			int j;
			for(j=0; j<i; j++)
				wordRead[j] = '\0';//���� 
			i = 0;
		}
        c = fgetc(file);
    }
    return tree;
}

BTNodeptr insertNode( BTNodeptr root , char wordRead[50])
{
	BTNodeptr cur, q;
	int flag = 0; 
	if(root == NULL)//���ڵ���� 
	{
		q = (BTNodeptr)malloc(sizeof(struct node));
		strcpy(q->word , wordRead);
		q->cnt = 1;
		q->left = q->right = NULL;
		
		root = q ;
		flag = 1;
	}
	
	cur = root;
	while(cur->left != NULL || cur->right != NULL)
	{
		if(strcmp(wordRead , cur->word) == 0)
		{
			cur->cnt++;
			flag = 1;
			break;
		}
		else if(strcmp(wordRead , cur->word) < 0 && cur->left != NULL)		
			cur = cur->left;
		else if(strcmp(wordRead , cur->word) > 0 && cur->right != NULL) 		
			cur = cur->right;
		else break;
	}
	
	if(flag == 0)//Ҷ�ڵ���� 
	{
		q = (BTNodeptr)malloc(sizeof(struct node));
		strcpy(q->word , wordRead);
		q->cnt = 1;
		q->left = q->right = NULL;
		
		if(strcmp(wordRead , cur->word) == 0)
			cur->cnt++;
		
		else if(strcmp(wordRead , cur->word) < 0)
		{
			cur->left = q;
			//printf("%s\n", cur->left->word);
		}			

		else if(strcmp(wordRead , cur->word) > 0)
		{
			cur->right = q;
			//printf("%s\n", cur->right->word);
		} 
		
		//printf("%d %s %d\n", ++test, cur->word, cur->cnt);
	}
	return root;
}

void inorderPrint(BTNodeptr t)//������� ��ӡ 
{
    if(t!=NULL)
	{
	    inorderPrint(t->left);
        printf("%s %d\n", t->word, t->cnt);//VISIT(T);/* ����Tָ���  */
        inorderPrint(t->right);
	}
}

