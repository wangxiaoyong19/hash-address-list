#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "hash.h"
char address[100];
int flag=0, i;
HashTable ht,ht2;
int initialize (void)
{
    printf("正在进行初始化");
    FILE *fp;
    userdata ip;
    fp = fopen("employee.txt", "r");
    printf("……");
    if (fp == NULL)
    {
        printf("\n文件打开失败，请检查文件名及路径是否正确、文件是否存在！\n");
        return 0;
    }

    while(fscanf(fp,"%s %lld %s",ip.username,&ip.phone,ip.address)==3)
    {
        HashInsert(ht,ip,'n');
        HashInsert(ht2,ip,'p');
    }
    fclose(fp);
    printf("\n");
    return 1;
}
int writefp(HashTable ht)
{
    int i;
    FILE *fp;
    fp = fopen("employee.txt", "w");
    setbuf(fp,NULL);
    printf("正在写入！\n");
    if (fp == NULL)
    {
        printf("\n文件打开失败，请检查文件名及路径是否正确、文件是否存在！\n");
        return 0;
    }
    for(i=0;i<HASHSIZE;i++)
		if(ht[i].data.username[0]!=DELFLAG &&ht[i].data.username[0]!=NULL)
			fprintf(fp,"%s %lld %s\n",ht[i].data.username,ht[i].data.phone,ht[i].data.address);
    fflush(fp);
    fclose(fp);
    return 1;
}
void Gettime(FILE *fp)
{ 
	time_t t;
	struct tm *lt;
	time (&t);                        
	lt = localtime (&t);                         
	fprintf (fp, "\n %d/%d/%d %02d:%02d:%02d\n",lt->tm_year+1900, lt->tm_mon+1, lt->tm_mday, lt->tm_hour, lt->tm_min, lt->tm_sec); 
}
int writelog(char output[])
{
    FILE *fp;
    fp = fopen("log.dat","a");
    setbuf(fp,NULL);
    Gettime(fp);
    fwrite(output,strlen(output),1,fp);
    fflush(fp);
    fclose(fp);
    return 1;
}