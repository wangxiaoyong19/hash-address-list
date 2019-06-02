#include <stdio.h>
#include <math.h>
#include <string.h>

#define HASHSIZE 100
#define DELFLAG -1

typedef struct {
    char username[20];
    long long int phone;
    char address[100];
}userdata;

typedef struct{
    userdata data;
    int times;
}HashTable[HASHSIZE];
/*hash函数*/
int HashFunc(long long int key)
{
	return key % HASHSIZE;
}

/*平方探查*/
int Collision2(int d,int i)
{
	if(i>0)
		return (int)(d+i*i) % HASHSIZE;
	else
	{
		return(int)(d-i*i)%HASHSIZE;
	}
	
}



/*算法8-7Hash查找*/
int HashSearch(HashTable ht,userdata x,char np)
{
	int addr,i = 0;
	if(np == 'n')
	{
		addr=HashFunc(x.username[0]);                                                          
		while(ht[addr].data.username[0]!=NULL &&ht[addr].data.username[0]!=-1&& strcmp(x.username,ht[addr].data.username)!=0||addr<0)
			{
				addr=Collision2(HashFunc(x.username[0]),i);
				if(i>0)
					i = -i;
				else
				{
					i=-i;
					i++;
				}
				
			}
		if(strcmp(x.username,ht[addr].data.username)==0)
			return addr;
		else
			return -addr;
	}
	else if(np == 'p')
	{
		addr=HashFunc(x.phone);                                                          
		while(ht[addr].data.phone!=NULL &&ht[addr].data.phone!=-1&& ht[addr].data.phone!=x.phone||addr<0)
			{
				addr=Collision2(HashFunc(x.phone),i);
				if(i>0)
					i = -i;
				else
				{
					i=-i;
					i++;
				}
			}
		if(x.phone==ht[addr].data.phone)
			return addr;
		else
			return -addr;
	}
}

/*算法8-8Hash插入*/
int HashInsert(HashTable ht,userdata x,char np)
{
	int addr;
	addr=HashSearch(ht,x,np);
	if(addr>0) return 0;
	ht[-addr].data=x;
	ht[-addr].times=1;
	return 1;
}


/*算法8-11显示Hash*/
void DisplayHash(HashTable ht,int np)
{
	int i;
	printf("员工信息如下(哈希序号，姓名，电话号码，住址):\n");
	if(np=='n')
	{
		for(i=0;i<HASHSIZE;i++)
			if(ht[i].data.username[0]!=DELFLAG &&ht[i].data.username[0]!=NULL)
				printf("%d,%s,%lld,%s\n",i,ht[i].data.username,ht[i].data.phone,ht[i].data.address);
	}
	else if(np=='p')
	{
		for(i=0;i<HASHSIZE;i++)
			if(ht[i].data.phone!=DELFLAG &&ht[i].data.phone!=NULL)
				printf("%d,%s,%lld,%s\n",i,ht[i].data.username,ht[i].data.phone,ht[i].data.address);
	}
	
}

/*算法8-10Hash删除*/
int HashDelete(HashTable ht,int addr,char np)
{
	if(np =='n')
	{
		if(addr>=0)
		{
			ht[addr].data.username[0]=DELFLAG;
			return 1;
		}
	}
	else if(np=='p')
	if(addr>=0)
	{
		ht[addr].data.phone=DELFLAG;
		return 1;
	}
	return 0;
}