#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 1024
struct link{
	char id[50];
	char name[50];
	int seat;
}; 
typedef struct link *Nodeptr;
Nodeptr list[max];

void readList(FILE *fp, int n);
void sortList_bySeat(int n);
void emptySeat(int Q, int n);
void repeatSeat(int Q, int n);
void sortList_byID(int n);
void printList(int n);
void fpprintList(FILE *fp, int n);

int main()
{
	int n = 0;
	scanf("%d", &n);
	FILE *fp1 = fopen("in.txt", "r");
	FILE *fp2 = fopen("out.txt", "w");
	
	readList(fp1, n);//座位表T1 
		//printf("T1\n");
		//printList(n);
		
	sortList_bySeat(n);//得到座位表T2 
		printf("T2\n");
		printList(n);		

	int M = list[n-1]->seat;
		printf("M:%d\n", M);
	int Q = M;
	if(n < M)	Q = n;
		printf("Q:%d\n", Q);
	
	emptySeat(Q, n);//除去漏排座位 
		printf("3\n");
		printList(n);
	sortList_bySeat(n);
		printf("4\n");
		printList(n);

	Q = list[n-1]->seat;
	repeatSeat(Q, n);//除去重复座位
		printf("5\n"); 
		printList(n);
		
	sortList_byID(n);
		printf("final\n");
		printList(n);
	
	fpprintList(fp2, n);
	fclose(fp1);
	fclose(fp2);
	return 0;
}

void readList(FILE *fp, int n){
	int i;
	Nodeptr p = NULL;
	char ID[50]={'\0'};
	char NAME[50]={'\0'};
	for(i = 0; i<n; i++)
	{
		p = (Nodeptr)malloc(sizeof(struct link));
		fscanf(fp,"%s%s%d", ID, NAME, &p->seat);
		strcpy(p->id, ID);
		strcpy(p->name, NAME);
		list[i] = p;
		printf("%s %s %d\n", list[i]->id, list[i]->name, list[i]->seat);
		printf("%d\n", i);
	}
	
}

void sortList_bySeat(int n){
	int i, j, flag=1;//bubbleSort
	Nodeptr temp = NULL;
	for(i = n-1; i>0 && flag==1; i--){
    	flag = 0;                   /* 每趟排序前标志flag置0 */ 
        for(j = 0; j < i; j++){		//j<i因为j+1 = i是最大 
        	if(list[j]->seat > list[j+1]->seat){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;  	/* 交换两个元素的位置 */     
                flag = 1;          	/* 标志flag置1 */ 
        	}
		}    
	}
}

void emptySeat(int Q, int n){
	int i = 0, j = 0;
	int flag[max];
	memset(flag, 0, sizeof(flag));
	for(i=0; i<n; i++){
		if(list[i]->seat <= Q)
			flag[list[i]->seat] = 1;
	}

	j = n-1;
	for(i = 1; i <= Q; i++){
		if(flag[i] == 0 && list[j]->seat > i)//补空座位补到共同中点 
		{
			list[j--]->seat = i;
		}

	}

} 

void repeatSeat(int Q, int n){
	int i, j;
	for(i = 0; i<n-1; i++)
	{
		if(list[i]->seat == list[i+1]->seat)
		{
			Q++;
			list[i+1]->seat = Q;
		}
	}
} 

void sortList_byID(int n){
	int i, j, flag=1;//bubbleSort
	Nodeptr temp = NULL;
	for(i = n-1; i>0 && flag==1; i--){
    	flag = 0;                   /* 每趟排序前标志flag置0 */ 
        for(j = 0; j < i; j++){		//j<i因为j+1 = i是最大 
        	if(strcmp(list[j]->id, list[j+1]->id) > 0){
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;  	/* 交换两个元素的位置 */     
                flag = 1;         	/* 标志flag置1 */ 
        	}
		}    
	}
}

void fpprintList(FILE *fp, int n){
	int i;
	for(i = 0; i < n; i++){
		fprintf(fp, "%s %s %d\n", list[i]->id, list[i]->name, list[i]->seat);
	}
}

void printList(int n){
	int i;
	for(i = 0; i < n; i++){
		printf("%s %s %d\n", list[i]->id, list[i]->name, list[i]->seat);
	}
}

