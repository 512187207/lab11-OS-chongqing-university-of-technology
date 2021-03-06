

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define false 0 
#define true 1 
#define n 4 
#define m 10 

struct 
{ 
char type[10]; /*设备类名*/ 
int count; /*拥有设备台数*/ 
int remain; /*现存的可用设备台数*/ 
int address; /*该类设备在设备表中的起始地址*/ 
}equiptype[n]; /*设备类表定义，假定系统有n个设备类型*/ 

struct 
{ 
int number; /*设备绝对号*/ 
int status; /*设备好坏状态*/ 
int remain; /*设备是否已分配*/ 
char jobname[4];/*占有设备的作业名*/ 
int lnumber; /*设备相对号*/ 
}equipment[m]; /*设备表定义，假定系统有m个设备*/ 



int allocate(char *J,char*type,int mm)  
{ 
    int i,t,j; /*查询该类设备*/ 
    i=0; 
    while(i<n&&strcmp(equiptype[i].type,type)!=0){ 
        i++; 
        if(i>=n)/*没有找到该类设备*/ 
        { 
            printf("无该类设备,设备分配失败"); 
            return(false); 
        } 
        if(equiptype[i].remain<1)/*所需设备现存可用台数不足*/ 
        {    
            printf("该类设备不足，分配失败"); 
            return(false); 
        } 
    }

    t=equiptype[i].address;/* 取出该类设备在设备表中的起始地址*/ 
    while(1) 
    {
/*填写作业名、相对号，状态改为已分配*/ 
        if(equipment[t].status==1 && equipment[t].remain==0){
            equiptype[i].remain--; 
            equipment[t].remain=1; 
            strcpy(equipment[t].jobname,J); 
            equipment[t].lnumber=mm;
            break;
        }
        if(t > 9 ){
            return 0;
        }
        t++; 

    }
    return 1; 
}/*设备分配函数结束*/ 

int reclaim (char *J,char *type) 
{ 
    int i,t,j,k,nn; 
    i=0; 
    while(i<n&&strcmp(equiptype[i].type,type)!=0) {
        i++; 
        if(i>=n)/*没有找到该类设备*/ 
        { 
            printf("无该类设备,设备回收失败"); 
            return(false); 
        }
    }     
    t=equiptype[i].address; /*取出该类设备在设备表中的起始地址*/ 
    j=equiptype[i].count; /*取出该类设备的数量*/ 
    k=0; 
    nn=t+j; 
    for(;t<nn;t++) {
        if((strcmp(equipment[t].jobname,J) == 0) && (equipment[t].remain == 1)) 
        { 
            equipment[t].remain=0; 
            equipment[t].lnumber = 0; 
            strcpy(equipment[t].jobname,"");  //清空job 
            k++; 
        }
    } 
    equiptype[i].remain= equiptype[i].remain+k;
    if(k==0) {
        printf("该作业没有使用该类设备\n"); 
        return(false);
    }
    return 1;
}/*设备回收函数结束*/ 

int main()
{ 
    char J[4]; 
    int i,mm,a; 
    char type[10]; 
/*设备类表初始化：*/ 
    strcpy(equiptype[0].type,"input");/*输入机*/ 
    equiptype[0].count=2; 
    equiptype[0].remain=2; 
    equiptype[0].address=0; 
    strcpy(equiptype[1].type,"printer");/*打印机 */ 
    equiptype[1].count=3; 
    equiptype[1].remain=3; 
    equiptype[1].address=2; 
    strcpy(equiptype[2].type,"disk");/*磁盘机*/ 
    equiptype[2].count=4; 
    equiptype[2].remain=4; 
    equiptype[2].address=5; 
    strcpy(equiptype[3].type,"tape");/*磁带机*/ 
    equiptype[3].count=1; 
    equiptype[3].remain=1; 
    equiptype[3].address=9; 
    /*设备表初始化：*/ 
    for(i=0;i<10;i++){ 
        equipment[i].number=i; 
        equipment[i].status=1; 
        equipment[i].remain=0; 
    } 
    while(1) 
    { 
        printf("\n0－退出，1－分配，2－回收，3－显示"); 
        printf("\n选择功能项（0~3）:"); 
        scanf("%d",&a); 
        switch(a) 
        { 
            case 0 : /*a=0程序结束*/ 
            exit(0); 
            case 1 : /*a=1分配设备*/ 
            printf("输入作业名、作业所需设备类和设备相对号"); 
            scanf("%s%s%d",J,type,&mm); 
            allocate(J,type,mm);/*分配设备*/ 
            break; 
            case 2: /*a=2回收设备*/ 
            printf("输入作业名和作业归还的设备类"); 
            scanf("%s%s",J,type); 
            reclaim(J,type);/*回收设备*/ 
            break; 
            case 3: /*a=3 输出设备类表和设备表的内容*/ 
            printf("\n输出设备类表\n"); 
            printf(" 设备类型 设备总量 空闲好设备\n"); 
            for(i=0;i<n;i++) 
                printf("%9s%8d%9d\n",equiptype[i].type,equiptype[i].count, equiptype[i].remain); 
                printf("输出设备表:\n"); 
                printf("绝对号 好/坏 已/未分配 占用作业名 相对号\n"); 
            for(i=0;i<m;i++) 
                printf("%3d%8d%9d%12s%8d\n",equipment[i].number, equipment[i].status,equipment[i].remain,equipment[i].jobname,equipment[i].lnumber); 
        } 
    } 
}


