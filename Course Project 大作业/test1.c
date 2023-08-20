#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char Stop_words[500][30];//ͣ��
char Article[7000000+10];//����
typedef struct word{//���� ���ڿ����ֵ���
    char alpha_word[30];
    int fre;//����Ƶ��
}word;
typedef struct sentence{//���� ���ڿ���Ͱ����
    char whole_sentence[3000];//�����Ľ����Ӵ洢
    int sum_fre;//���ӵ���Ƶ��
}sentence;

word word_list[1000000];//�ʻ��
int word_list_lenth,Stop_lenth;
sentence sentence_list[500000];//���ӱ�
char word_temp[30];//temp

int find_stop_words(char word[]);//�жϵ����Ƿ�ͣ��
int find_word_in_word_list(char word[]);//�жϵ����Ƿ��Ѿ������ڴʻ����
int work_out_sum_fre(char sentence_1[]);
int find_word(char word_1[]);
char lower_to_upper(char x);//Сд->��д

int comp(const void*a,const void *b) {
    word aa = *(word*)a;
    word bb = *(word*)b;
    return aa.fre-bb.fre;
}

int comp_sentence(const void*a,const void *b) {
    sentence aa = *(sentence*)a;
    sentence bb = *(sentence*)b;
    return bb.sum_fre - aa.sum_fre;
}


int main()
{
    FILE *stop,*in,*out;
    int N,i,Article_lenth;
	stop=fopen("stopwords.txt","r");
	in=fopen("article.txt","r");
	Article_lenth=fread(Article,1,7000010,in);
	Article_lenth=strlen(Article);
	//Stop_lenth=fread(Stop_words,1,2500,stop);
	Stop_lenth=0;
	while(fscanf(stop,"%s",Stop_words[Stop_lenth++])!=EOF) ;
	fclose(in);
	fclose(stop);
	//����
	word_list_lenth=0;
	scanf("%d",&N);//���N��
	int sentence_pos=0,word_temp_pos=0,single_sentence_pos=0;
	char al_x;
    for(i=0;i<Article_lenth;i++){
        if(single_sentence_pos==0&&Article[i]==' ') continue;
        sentence_list[sentence_pos].whole_sentence[single_sentence_pos++]=Article[i];
        if(isalpha(Article[i])){
            al_x=lower_to_upper(Article[i]);
            word_temp[word_temp_pos++]=al_x;
        }
        else{
            if(!find_stop_words(word_temp)){
                find_word_in_word_list(word_temp);
            }
            int p;
            for(p=0;p<word_temp_pos+1;p++){
                word_temp[p]='\0';
            }
            word_temp_pos=0;
        }
        if(Article[i]=='.'||Article[i]=='?'||Article[i]=='!'){
            sentence_pos++;
            //printf("%d\n", sentence_pos);
            single_sentence_pos=0;
        }
    }
    /*
    qsort(word_list,word_list_lenth,sizeof(word_list[1]),comp);
    for(i=0;i<word_list_lenth;i++){
        printf("%s %d\n",word_list[i].alpha_word,word_list[i].fre);
    }
    */
    /*
    for(i=0;i<sentence_pos;i++){
        printf("%s\n",sentence_list[i].whole_sentence);
    }
    */
    for(i=0;i<sentence_pos;i++){
        sentence_list[i].sum_fre=work_out_sum_fre(sentence_list[i].whole_sentence);
    }
    qsort(sentence_list,sentence_pos,sizeof(sentence_list[1]),comp_sentence);
    /*
    for(i=0;i<sentence_pos;i++){
        printf("%d %s\n\n",sentence_list[i].sum_fre,sentence_list[i].whole_sentence);
    }
    */
    for(i=0;i<5;i++){
        printf("%d %s\n",sentence_list[i].sum_fre,sentence_list[i].whole_sentence);
    }
    out=fopen("results.txt","w");
    for(i=0;i<N;i++){
        fprintf(out,"%d %s\n",sentence_list[i].sum_fre,sentence_list[i].whole_sentence);
    }
    fclose(out);
    return 0;
}

int find_stop_words(char word[])
{int i;
    for(i=0;i<Stop_lenth;i++){
        if(strcmp(word,Stop_words[i])==0){
            return 1;//���������ͣ���򷵻�1
        }
    }
    return 0;//���Ƿ���0
}

int find_word_in_word_list(char word[])
//�ڴʻ����Ѱ�ҵ��ʣ����ҵ���Ƶ��+1��û�ҵ������ʼ���ʻ��
{int i;
    for(i=0;i<word_list_lenth;i++){
        if(strcmp(word,word_list[i].alpha_word)==0){//����ҵ�
            word_list[i].fre++;//Ƶ��+1
            return i;
        }
    }
    strcpy(word_list[word_list_lenth].alpha_word,word);//����ʻ��
    word_list[word_list_lenth].fre=1;//Ƶ�ȳ�ֵΪ1
    word_list_lenth++;//lenth++
    //printf("%d\n", word_list_lenth);
    return -1;
}

int work_out_sum_fre(char sentence_1[])
{
    int res=0;
    int i,p;
    int lenth=strlen(sentence_1);
    int word_temp_pos=0;
    char al_x;
    for(p=0;p<29;p++){
        word_temp[p]='\0';
    }
    for(i=0;i<lenth;i++){
        if(isalpha(sentence_1[i])){//�������ĸ
            al_x=lower_to_upper(sentence_1[i]);//תΪСд
            word_temp[word_temp_pos++]=al_x;//��¼�����ĸ
        }
        else{//������ĸ��˵����һ�����ʽ�����
            res+=find_word(word_temp);//Ѱ��������ʵ�Ƶ��
            word_temp_pos=0;
			int p;
            for(p=0;p<29;p++){
                word_temp[p]='\0';
            }
        }
    }
    return res;
}

int find_word(char word_1[])
{
    int i;
    for(i=0;i<word_list_lenth;i++){
        if(strcmp(word_list[i].alpha_word,word_1)==0){
                return word_list[i].fre;//�ҵ��˷���Ƶ��
        }
    }
    return 0;//û�ҵ�����0
}

char lower_to_upper(char x)
{
    return (x>='A'&&x<='Z')?(x|0x20):x;//������������ʽҲ����
}

