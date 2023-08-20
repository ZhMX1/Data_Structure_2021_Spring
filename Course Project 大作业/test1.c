#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
char Stop_words[500][30];//停词
char Article[7000000+10];//文章
typedef struct word{//单词 后期考虑字典树
    char alpha_word[30];
    int fre;//出现频率
}word;
typedef struct sentence{//句子 后期考虑桶排序
    char whole_sentence[3000];//完整的将句子存储
    int sum_fre;//句子的总频率
}sentence;

word word_list[1000000];//词汇表
int word_list_lenth,Stop_lenth;
sentence sentence_list[500000];//句子表
char word_temp[30];//temp

int find_stop_words(char word[]);//判断单词是否停词
int find_word_in_word_list(char word[]);//判断单词是否已经出现在词汇表中
int work_out_sum_fre(char sentence_1[]);
int find_word(char word_1[]);
char lower_to_upper(char x);//小写->大写

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
	//读入
	word_list_lenth=0;
	scanf("%d",&N);//输出N个
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
            return 1;//如果单词是停词则返回1
        }
    }
    return 0;//不是返回0
}

int find_word_in_word_list(char word[])
//在词汇表中寻找单词，若找到则频度+1，没找到将单词加入词汇表
{int i;
    for(i=0;i<word_list_lenth;i++){
        if(strcmp(word,word_list[i].alpha_word)==0){//如果找到
            word_list[i].fre++;//频度+1
            return i;
        }
    }
    strcpy(word_list[word_list_lenth].alpha_word,word);//加入词汇表
    word_list[word_list_lenth].fre=1;//频度初值为1
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
        if(isalpha(sentence_1[i])){//如果是字母
            al_x=lower_to_upper(sentence_1[i]);//转为小写
            word_temp[word_temp_pos++]=al_x;//记录这个字母
        }
        else{//不是字母，说明上一个单词结束了
            res+=find_word(word_temp);//寻找这个单词的频度
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
                return word_list[i].fre;//找到了返回频度
        }
    }
    return 0;//没找到返回0
}

char lower_to_upper(char x)
{
    return (x>='A'&&x<='Z')?(x|0x20):x;//这里用其他方式也可以
}

