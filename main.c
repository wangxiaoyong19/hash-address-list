#include "fp.h"
#include<time.h>
int main(void)
{
    userdata ipp;
    int i,address;
    i = initialize();
    char YN,pn;
    if(i == 0)
    {
        return 0;
    }
    printf("欢迎使用员工信息管理系统。\n");
    printf("我们将引导你进行接下来的工作。\n");
    while(1){
        printf("\n\n------------------------------------------------------\n");
        printf("首先请按照下面的序号选择你所需要的工作：\n");
        printf("1、插入一个员工的数据。\n");
        printf("2、查找员工数据。\n");
        printf("3、删除一个员工。\n");
        printf("4、修改员工信息。\n");
        printf("5、显示全部员工信息。\n");
        printf("6、退出\n");
        printf("请键入您的选择以便我们继续进行：");
        scanf("%d",&i);
        getchar();
        switch(i)
        {
            case 1:
                printf("请输入一个员工数据（格式为 用户名（拼音） 电话号码 地址）：");
                scanf("%s %lld %s",ipp.username,&ipp.phone,ipp.address);
                HashInsert(ht,ipp,'n');
                HashInsert(ht2,ipp,'p');
                writelog("写入");
                printf("完成。\n");
                break;
            case 2:
                printf("请选择使用哪种查找方式：\n1，姓名查找\n2，电话号码查找\n");
                scanf("%c",&YN);
                if(YN=='1')
                {
                printf("请输入你想要查找的员工姓名：");
                scanf("%s",ipp.username);
                getchar();
                address = HashSearch(ht,ipp,'n');
                }
                else if(YN=='2')
                {
                    printf("请输入你想要查找的电话号码：");
                    scanf("%lld",&ipp.phone);
                    address = HashSearch(ht2,ipp,'p');
                }
                if(address>=0)
                {
                    printf("你所查找的员工位置为：%d",address);
                    printf("他的完整信息如下：%s,%lld,%s",ht[address].data.username,ht[address].data.phone,ht[address].data.address);
                    printf("完成。\n");
                    writelog("查找\n");
                }
                if(address<0)
                {
                    printf("查无此人，请检查你的输入是否正确\n");
                }
                break;
            case 3:
                printf("请选择使用哪种查找方式以找到你要删除的员工目标：\n1，姓名查找\n2，电话号码查找\n");
                scanf("%c",&pn);
                getchar();
                if(pn=='1')
                {
                    printf("请输入要删除的员工姓名：");
                    scanf("%s",ipp.username);
                    getchar();
                    address = HashSearch(ht,ipp,'n');
                }
                else if(pn=='2')
                {
                    printf("请输入要删除的员工电话号码：");
                    scanf("%lld",&ipp.phone);
                    address = HashSearch(ht2,ipp,'p');
                }
                if(address<0)
                {
                    printf("未找到！！\n");
                    break;
                }
                printf("他的完整信息如下：%s,%lld,%s",ht[address].data.username,ht[address].data.phone,ht[address].data.address);
                printf("\n是否确认删除（Y/N）：");
                scanf("%c",&YN);
                getchar();
                if(YN =='Y'||YN=='y')
                {
                    if(pn=='1')
                    {
                        if(HashDelete(ht2,HashSearch(ht2,ht[address].data,'p'),'p')==1&&HashDelete(ht,address,'n')==1)
                            printf("完成。\n");
                    }
                    else
                    {
                        if(HashDelete(ht,HashSearch(ht,ht[address].data,'n'),'n')==1&& HashDelete(ht2,address,'p')==1)
                            printf("完成。\n");
                    }
                    
                    writelog("删除\n");
                }
                break;
            case 4:
                printf("请选择使用哪种查找方式以找到你要修改的员工目标：\n1，姓名查找\n2，电话号码查找\n");
                scanf("%c",&pn);
                getchar();
                if(pn=='1')
                {
                    printf("请输入要修改的员工姓名：");
                    scanf("%s",ipp.username);
                    getchar();
                    address = HashSearch(ht,ipp,'n');
                    if(address<0){
                        printf("查无此人！请检查自己的输入是否有误\n");
                        break;
                    }
                }
                else if(pn=='2')
                {
                    printf("请输入要修改的员工电话号码：");
                    scanf("%lld",&ipp.phone);
                    getchar();
                    address = HashSearch(ht2,ipp,'p');
                    if(address<0){
                        printf("查无此人！请检查自己的输入是否有误\n");
                        break;
                    }
                }
                printf("您可以通过以下方式进行修改：\na,仅修改姓名\nb,仅修改电话号码\nc,仅修改地址\nd,全部修改\n");
                printf("请输入要修改的方式：");
                scanf("%c",&YN);
                getchar();
                switch(YN){
                    case 'a':
                        printf("请输入新的员工姓名：");
                        scanf("%s",ipp.username);
                        getchar();
                        if(pn=='1')
                        {
                            printf("他的原有姓名为：%s\n",ht[address].data.username);
                            printf("你即将变更的姓名为：%s\n",ipp.username);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            getchar();
                            if(YN=='Y'||YN=='y')
                                {
                                    strcpy(ipp.address,ht[address].data.address);
                                    ipp.phone = ht[address].data.phone;
                                    HashInsert(ht,ipp,'n');
                                    ht[address].data.username[0] = DELFLAG;
                                    strcpy(ht2[HashSearch(ht2,ipp,'p')].data.username,ipp.username);
                                    printf("完成。\n");
                                }
                        }
                        else
                        {
                            printf("他的原有姓名为：%s\n",ht2[address].data.username);
                            printf("你即将变更的姓名为：%s\n",ipp.username);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            getchar();
                            if(YN=='Y'||YN=='y')
                                {
                                    
                                    strcpy(ipp.address,ht2[address].data.address);
                                    ipp.phone = ht2[address].data.phone;
                                    HashInsert(ht,ipp,'n');
                                    ht[HashSearch(ht,ht2[address].data,'n')].data.username[0] = DELFLAG;
                                    strcpy(ht2[address].data.username,ipp.username);
                                    printf("完成。\n");
                                }
                        }
                        
                            break;
                            case 'b':
                            printf("请输入新的电话号码：");
                            scanf("%lld",&ipp.phone);
                            getchar();
                            if(pn=='n')
                            {
                                printf("他的原有电话号码为：%lld\n",ht[address].data.phone);
                                printf("你即将变更的电话号码为：%lld\n",ipp.phone);
                                printf("是否确认修改(Y/N)：");
                                scanf("%c",&YN);
                                if(YN=='Y'||YN=='y')
                                    {
                                        strcpy(ipp.address,ht[address].data.address);
                                        HashDelete(ht2,HashSearch(ht,ht[address].data,'p'),'p');
                                        HashInsert(ht2,ipp,'p');
                                        ht[address].data.phone=ipp.phone;
                                        printf("完成。\n");
                                    }
                            }
                            else
                            {
                                printf("他的原有电话号码为：%lld\n",ht2[address].data.phone);
                                printf("你即将变更的电话号码为：%lld\n",ipp.phone);
                                printf("是否确认修改(Y/N)：");
                                scanf("%c",&YN);
                                if(YN=='Y'||YN=='y')
                                    {
                                        ht[HashSearch(ht,ht2[address].data,'n')].data.phone = ipp.phone;
                                        strcpy(ipp.username,ht2[address].data.username);
                                        strcpy(ipp.address,ht2[address].data.address);
                                        HashDelete(ht2,address,'p');
                                        HashInsert(ht2,ipp,'p');
                                        printf("完成。\n");
                                    }
                            }
                            
                        break;
                        case 'c':
                        printf("请输入新的地址：");
                        scanf("%s",ipp.address);
                        getchar();
                        if(pn=='n'){
                            printf("他的原有地址为：%s\n",ht[address].data.address);
                            printf("你即将变更的地址为：%s\n",ipp.address);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            if(YN=='Y'||YN=='y')
                                {
                                    strcpy(ht[address].data.address,ipp.address);
                                    strcpy(ht2[HashSearch(ht2,ht[address].data,'p')].data.address,ipp.address);
                                    printf("完成。\n");
                                }
                        }
                        else{
                            printf("他的原有地址为：%s\n",ht2[address].data.address);
                            printf("你即将变更的地址为：%s\n",ipp.address);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            getchar();
                            if(YN=='Y'||YN=='y')
                                {
                                    strcpy(ht2[address].data.address,ipp.address);
                                    strcpy(ht[HashSearch(ht,ht2[address].data,'p')].data.address,ipp.address);
                                    printf("完成。\n");
                                }
                        }
                        break;
                        case 'd':
                        printf("请输入新的数据（用户名（拼音） 电话号码 地址）：");
                        scanf("%s %lld %s",ipp.username,&ipp.phone,ipp.address);
                        getchar();
                        if(pn=='1')
                        {
                            printf("他的原有数据为（用户名（拼音） 电话号码 地址）：%s，%lld，%s\n",ht[address].data.username,ht[address].data.phone,ht[address].data.address);
                            printf("你即将变更数据为（用户名（拼音） 电话号码 地址）：%s，%lld，%s\n",ipp.username,ipp.phone,ipp.address);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            getchar();
                            if(YN=='Y'||YN=='y')
                                {
                                    HashInsert(ht2,ipp,'p');
                                    ht2[HashSearch(ht2,ht[address].data,'p')].data.phone=DELFLAG;
                                    HashInsert(ht,ipp,'n');
                                    ht[address].data.username[0] = DELFLAG;
                                    printf("完成。\n");
                                }
                        }
                        else
                        {
                            printf("他的原有数据为（用户名（拼音） 电话号码 地址）：%s，%lld，%s\n",ht2[address].data.username,ht2[address].data.phone,ht2[address].data.address);
                            printf("你即将变更数据为（用户名（拼音） 电话号码 地址）：%s，%lld，%s\n",ipp.username,ipp.phone,ipp.address);
                            printf("是否确认修改(Y/N)：");
                            scanf("%c",&YN);
                            getchar();
                            if(YN=='Y'||YN=='y')
                                {
                                    HashInsert(ht,ipp,'n');
                                    ht[HashSearch(ht,ht2[address].data,'n')].data.username[0] = DELFLAG;
                                    HashInsert(ht2,ipp,'p');
                                    ht2[address].data.phone = DELFLAG;
                                    printf("完成。\n");
                                }
                        }
                        
                        break;
                         default:
                        printf("错误！！\n");
                        break;
                         
                }
                writelog("修改\n");   
                break;
            case 5:
                printf("请选择要以哪个哈希表展示（1、姓名哈希表 2、电话哈希表）：");
                scanf("%c",&pn);
                getchar();
                if(pn=='1')
                    DisplayHash(ht,'n');
                else
                {
                    DisplayHash(ht2,'p');
                }
                
                printf("完成。\n");
                writelog("显示哈希表\n");
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("错误！！\n");
                writelog("错误操作\n");
                break;
        }
       writefp(ht);
    }
}