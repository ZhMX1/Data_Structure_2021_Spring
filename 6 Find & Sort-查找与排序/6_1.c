#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 50
#define NHASH  3001
#define MULT  37
struct link{
	char content[max];
	struct link *next;
};
typedef struct link *ptr;
ptr hashList[10050];
int cnt = 0;
int exist; 

int orderSearch(char list[][max], int n, char word[]);
int binsearch(char list[][max], int begin, int n, char word[]);
void createChart(int chart[], char list[][max], int n);
int indexSearch(int chart[], char list[][max], char word[]);
unsigned int hash(char *str);
ptr createNode(char word[]);
void insertNode(char word[]);
int hashSearch(char word[]);

int main()
{
	FILE *fp = fopen("dictionary3000.txt", "r");
	char list[3600][max];
	int i = 0, n = 0;	//N记录单词表长度 
	while(fscanf(fp, "%s", list[i]) != EOF)
	{
		insertNode(list[i]);//建立hash表
		i++;//读入所有字符
	}
		
	//fgets(str, max ,fp);这个最后会有一个回车符，比较返回值不准确  
	n = i;
	
	char word[max] = {'\0'};
	int op = 0, pos = 0;
	while(scanf("%s%d", word, &op) != EOF)
	{
		cnt = 0;
		exist = 0;
		if(op == 1)//顺序查找
		{
			pos = orderSearch( list, n, word ) + 1;
			cnt = pos; 
		} 
		
		else if(op == 2)//折半查找方式
		{
			pos = binsearch(list, 0, n, word);
			if(pos != -1) exist = 1;
		}
		
		else if(op == 3)//索引表
		{
			int chart[max];//记录同样字母开头的末位行数 
			memset(chart, 0, sizeof(chart));
			createChart(chart, list, n);
			
			//折半查找 
			pos = indexSearch(chart, list, word);
			if(pos != -1) exist = 1;
		}
		
		else if(op == 4)//hash函数
		{
			exist = hashSearch(word); 
		}
		printf("%d %d\n", exist, cnt);
	}

	return 0;
}

int orderSearch(char list[][max], int n, char word[])
{    
    int i;
    for(i = 0; i < n; i++)
    {	
		int cmp = strcmp(word, list[i]); 
		if(cmp == 0) {
    		exist = 1;
    		return i;
		}
		else if(cmp < 0){
			return i;
		}        
	}   
    return -1;
}

int binsearch(char list[][max], int begin, int n, char word[])
{
	int low = begin, high = n-1, mid;
    while(low <= high){
    	cnt++; 
    	mid = (low + high) / 2;
    	int cmp = strcmp(word, list[mid]); 
        if(cmp == 0 )
            return mid;             /*  查找成功  */
        else if(cmp > 0)
            low = mid + 1;            /*  准备查找后半部分 */
        else
        	high = mid - 1;           /* 准备查找前半部分 */
    }
        return -1;                    /*   查找失败  */
}

void createChart(int chart[], char list[][max], int n){
	int i;
	int c;
    for(i = 0; i < n; i++){
    	c = list[i][0] - 'a';
    	chart[c] = i;
	}
}

int indexSearch(int chart[], char list[][max], char word[])
{
	if(word[0] == 'a')
		return binsearch(list, 0, chart[word[0]-'a']+1, word);
	else
		return binsearch(list, chart[word[0]-'a'-1]+1, chart[word[0]-'a']+1, word);
}

/* compute hash value for string */
unsigned int hash(char *str){
    unsigned int h = 0;
    char *p;
    
    for(p = str; *p != '\0'; p++)
        h = MULT*h + *p;

    return h % NHASH;
}

ptr createNode(char word[])//创建一个新hash表内容 
{
    ptr q = (ptr)malloc(sizeof(struct link));
    q->next = NULL;
    strcpy(q->content ,word);
    return q;
}

void insertNode(char word[])//插入哈希表
{
    int addr = hash(word);//得到地址 
    ptr temp = hashList[addr];
    if(temp == NULL)//如果没发生冲突 
        hashList[addr] = createNode(word);//直接放入节点 

	else//向后移动找空指针
	{
    	while(temp->next != NULL)
            temp = temp->next;
        temp->next = createNode(word);//解决冲突放入节点 
    }
}

int hashSearch(char word[])
{
    int addr = hash(word);
    ptr temp = hashList[addr];//找到hash地址指针栈 
    
    if(temp == NULL) return 0;//指针栈无内容 
    else{
        while(temp != NULL)//向后查看该地址下所有内容 
		{
            cnt++;
            if(strcmp(word ,temp->content) == 0)
                return 1;

            else if(temp->next != NULL)
                temp = temp->next;
                
            else if(temp->next == NULL)
                return 0;
        }
    }
    return 0;
}

