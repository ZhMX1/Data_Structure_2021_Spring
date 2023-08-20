#include<stdio.h>
#include<math.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#define max 350
typedef struct wordNode{
	char word[105];
	int times;
	struct word *left, *right;
}wordNode, *wordPtr;

typedef struct sentenceNode{
	char sentence[3050];
	int frequence;
}sentenceNode, *sentencePtr;

void readTxt(FILE *file); 
int isStopWord(int begin, int n, char word[]);
wordPtr insertNode( wordPtr root, char wordRead[]);
int sumFreq(char wholeSentence[]);
int findFreq(char word[]);
int compare (const void * a, const void * b);

char stopWordList[max][30];//stopword���ʱ�
int stopWordCnt = 0;
char prstWord[105] = {'\0'};//��¼��ǰ���뵥�� 
char prstSentence[5050] = {'\0'};//��¼��ǰ������� 
int prstWordPos = 0, prstSentencePos = 0;//�ֱ��¼��ǰ���뵥�ʡ�����ַ�λ��
int sentenceCnt = 0;//��¼���ӱ��о����� 
int cntWord = 0;
sentenceNode sentenceList[200005];//���ӱ� 
wordPtr tree = NULL;//������ 

int main()
{
	FILE *fp = fopen("stopwords.txt", "r");
	FILE *IN = fopen("article.txt", "r");
	
	//stopword���ʱ���� 
	while(fscanf(fp, "%s", stopWordList[stopWordCnt++]) != EOF);
	fclose(fp);
	
	int N=0;//������ 
	scanf("%d", &N);
	
	memset(prstWord, 0, sizeof(prstWord));
	memset(prstSentence, 0, sizeof(prstSentence));
	readTxt(IN);
	//printf("sentenceCnt:%d\n",sentenceCnt);
	//printf("1\n");//�˲�֮ǰ������ȷ�� 
	
	int i = 0;
	for(i=0; i<sentenceCnt; i++)
		sentenceList[i].frequence = sumFreq(sentenceList[i].sentence);
	//printf("2\n");//�˲�֮ǰ������ȷ�� 
	//bubbleSort(sentenceList, sentenceCnt);
	qsort(sentenceList, sentenceCnt, sizeof(sentenceList[0]), compare);
	
	for(i=0; i<5; i++){
        printf("%d %s\n",sentenceList[i].frequence, sentenceList[i].sentence);
    }
    
	FILE *OUT = fopen("results.txt", "w");
	for(i=0; i<N; i++){
        fprintf(OUT,"%d %s\n",sentenceList[i].frequence, sentenceList[i].sentence);
    }
    fclose(IN);
	fclose(OUT);
	return 0;
}

int compare (const void * a, const void * b)
{
	sentenceNode aa = *(sentenceNode*)a;
    sentenceNode bb = *(sentenceNode*)b;
	return bb.frequence - aa.frequence;
}

void readTxt(FILE *file){
	char c = fgetc(file);
    while(c != EOF)
	{	
		//printf("%c ", c);
		if(prstSentencePos==0 && c == ' '){
			c = fgetc(file);
			continue;
		}
		prstSentence[prstSentencePos++] = c;
		
		if(isalpha(c)){
			c = tolower(c);
			prstWord[prstWordPos++] = c;
			//printf("%c \n", c);
			//prstSentence[prstSentencePos++] = c;
		}
		else{
			//���ַ����ж�stopword, ���������뵥�ʱ�
			//�ǡ���? �����ݵ����������-���飬�����ݵĵ�������� 
			if(prstWordPos != 0 && !isStopWord(0, stopWordCnt, prstWord)){ 
				//cntWord++;
				//printf("%d  %s\n",cntWord, prstWord);
				tree = insertNode(tree, prstWord);
			}	
			memset(prstWord, 0, sizeof(prstWord));
			prstWordPos = 0;
				 
			if((c=='.' || c=='?' || c=='!') && prstSentencePos!=0){
				strcpy(sentenceList[sentenceCnt++].sentence, prstSentence);
				//printf("%d\n",sentenceCnt);
				//puts(prstSentence);
				prstSentencePos = 0; 
				memset(prstSentence, 0, sizeof(prstSentence));
			}
		}
        c = fgetc(file);
    }	
}

int isStopWord(int begin, int n, char word[]){
	int low = begin, high = n-1, mid;
    while(low <= high){
    	mid = (low + high) / 2;
    	int cmp = strcmp(word, stopWordList[mid]); 
        if(cmp == 0 )
            return 1;             /*  ���ҳɹ�  */
        else if(cmp > 0)
            low = mid + 1;            /*  ׼�����Һ�벿�� */
        else
        	high = mid - 1;           /* ׼������ǰ�벿�� */
    }
        return 0;                    /*   ����ʧ��  */
} 

wordPtr insertNode( wordPtr root, char wordRead[]){
	wordPtr q, cur=NULL;
	int flag = 0; //��ʾ�����Ƿ�ִ���˲������ 
	if(root == NULL)//���ڵ���� 
	{
		q = (wordPtr)malloc(sizeof(struct wordNode));
		strcpy(q->word , wordRead);
		q->times = 1;
		q->left = q->right = NULL;
		root = q ;
		flag = 1;
		return root; 
	}
	
	cur = root;
	while(cur->left != NULL || cur->right != NULL)
	{
		if(strcmp(wordRead , cur->word) == 0)
		{
			cur->times++;
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
		q = (wordPtr)malloc(sizeof(struct wordNode));
		strcpy(q->word , wordRead);
		q->times = 1;
		q->left = q->right = NULL;
		
		if(strcmp(wordRead , cur->word) == 0)
			cur->times++;
		else if(strcmp(wordRead , cur->word) < 0){
			cur->left = q;
			//printf("%s\n", cur->left->word);
		}			
		else if(strcmp(wordRead , cur->word) > 0){
			cur->right = q;
			//printf("%s\n", cur->right->word);
		} 
	}
	return root;
}

int sumFreq(char wholeSentence[]){
	char tempWord[105]={'\0'};
	int i, j = 0, sum = 0;
	char c;
    int len = strlen(wholeSentence);
    for(i=0; i<len; i++){
    	if(isalpha(wholeSentence[i])){
			c = tolower(wholeSentence[i]);
			tempWord[j++] = c;
		}
		else{
			if(!isStopWord(0, stopWordCnt, tempWord)){
				//printf("%s", tempWord);
				sum += findFreq(tempWord);
			}	
			memset(tempWord, 0, sizeof(tempWord));
			j = 0;
		}
	}
	//printf("sum:%d\n", sum);
	return sum;	
}

int findFreq(char word[]){	
	wordPtr temp = tree;
	while(temp != NULL)
	{
		int cmp = strcmp(word, temp->word);
		if(cmp == 0){
			//printf("%d\n", temp->times);
			return temp->times;
		}
		else if(cmp < 0)
			temp = temp->left;
		else if(cmp > 0)
			temp = temp->right;
	}
	if(temp == NULL) return 0;
}


