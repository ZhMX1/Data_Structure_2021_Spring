#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 1024
int cnt = 0;
void selectSort(int k[ ],int n);
void bubbleSort(int k[ ],int n);
void heapSort(int k[ ],int n);
void adjust(int k[],int i,int n);
void mergeSort(int k[ ],int n);
void mSort(int k[], int tmp[], int left, int right);
void merge(int x[],int tmp[],int left, int leftend, int rightend);
void quickSort(int k[],int left, int right);
void swap(int *a, int *b);
int main()
{
	int n = 0, method = 0;
	scanf("%d%d", &n, &method);
	
	int i;
	int list[120];
	for(i = 0; i<n; i++){
		scanf("%d", &list[i]);
	}
	
	cnt = 0;
	if(method == 1)
	{
		selectSort(list, n);
	}
	else if(method == 2)
	{
		bubbleSort(list, n);
	}
	else if(method == 3)
	{
		heapSort(list, n);
	}
	else if(method == 4)
	{
		mergeSort(list, n);
	}
	else if(method == 5)
	{
		quickSort(list, 0, n-1);
	}
	for(i = 0; i<n; i++)
		printf("%d ", list[i]);
	printf("\n%d", cnt);
	return 0;
}

void selectSort(int k[ ],int n)   
{     
	int i, j, d;
	int temp;
	for(i=0;i<n-1;i++){
		d = i;
		for(j=i+1; j<n; j++)
		{
			cnt++;
			if(k[j]<k[d])
				d = j;
		}
		if(d != i){/* 最小值元素非未排序元素的第一个元素时 */
			temp = k[d] ;
			k[d] = k[i];
			k[i] = temp;
       	}
    }
}

void bubbleSort(int k[ ],int n)
{     
	int i, j, flag=1;
	int temp;
	for(i=n-1; i>0 && flag==1; i--){
        flag = 0;                        /* 每趟排序前标志flag置0 */ 
        for(j = 0; j<i; j++){
        	cnt++;
        	if(k[j]  > k[j+1]){
                temp = k[j];
            	k[j] = k[j+1];
                k[j+1] = temp;  /* 交换两个元素的位置 */     
                flag = 1;              /* 标志flag置1 */ 
            }
		}
        	
    }
}

void heapSort(int k[],int n)
{
	int i;
    int temp;
    for(i = n/2-1; i>=0; i--)
    	adjust(k,i,n);
	for(i = n-1; i>=1; i--){
        temp = k[i];
        k[i] = k[0];
        k[0] = temp;
		adjust(k,0,i);
    }
}
void adjust(int k[],int i,int n)
{
    int j, temp;
    temp = k[i];
    j = 2*i + 1;
    while(j < n){
        if(j<n-1 && k[j]<k[j+1])
            j++;
		cnt++;
        if(temp >= k[j]) 
            break;
        k[(j-1)/2] = k[j];
        j = 2*j+1;
    }
    k[(j-1)/2] = temp;
}

void mergeSort(int k[ ],int n)
{
    int *tmp;
    tmp = (int *)malloc(sizeof(int) * n);
    if(tmp != NULL) {
        mSort(k, tmp, 0, n-1);
        free(tmp);
    } 
    else
        printf("No space for tmp array!!!\n");
}
void mSort(int k[], int tmp[], int left, int right)
{
    int center;
    if(left < right){
        center = (left+right)/2;
        mSort(k, tmp, left, center);
        mSort(k, tmp, center+1, right);
        merge(k, tmp, left, center, right);
    }
}
void merge(int x[],int tmp[],int left, int leftend, int rightend)
{     
    int i=left, j=leftend+1, q=left;
    while(i<=leftend && j<=rightend)
    {
    	cnt++;
        if(x[i] <= x[j]) 
            tmp[q++] = x[i++];
        else
            tmp[q++] = x[j++];
    }
    while(i <= leftend)
        tmp[q++] = x[i++];
    while(j <= rightend)
        tmp[q++] = x[j++];
    for(i = left; i <= rightend; i++)
        x[i] = tmp[i];
}

void quickSort(int k[],int left, int right)
{    
    int i, last;
    if(left<right){
        last=left; 
        for(i=left+1;i<=right;i++)
        {
        	cnt++;
        	if(k[i] < k[left])
                swap(&k[++last], &k[i]);
		}    
        swap(&k[left], &k[last]);
        quickSort(k,left,last-1); 
        quickSort(k,last+1,right);   
    }
}
void swap(int *a, int *b)
{
    int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
 }

