

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

#define false 0 
#define true 1 
#define n 4 
#define m 10 

struct 
{ 
char type[10]; /*�豸����*/ 
int count; /*ӵ���豸̨��*/ 
int remain; /*�ִ�Ŀ����豸̨��*/ 
int address; /*�����豸���豸���е���ʼ��ַ*/ 
}equiptype[n]; /*�豸������壬�ٶ�ϵͳ��n���豸����*/ 

struct 
{ 
int number; /*�豸���Ժ�*/ 
int status; /*�豸�û�״̬*/ 
int remain; /*�豸�Ƿ��ѷ���*/ 
char jobname[4];/*ռ���豸����ҵ��*/ 
int lnumber; /*�豸��Ժ�*/ 
}equipment[m]; /*�豸�����壬�ٶ�ϵͳ��m���豸*/ 



int allocate(char *J,char*type,int mm)  
{ 
    int i,t,j; /*��ѯ�����豸*/ 
    i=0; 
    while(i<n&&strcmp(equiptype[i].type,type)!=0){ 
        i++; 
        if(i>=n)/*û���ҵ������豸*/ 
        { 
            printf("�޸����豸,�豸����ʧ��"); 
            return(false); 
        } 
        if(equiptype[i].remain<1)/*�����豸�ִ����̨������*/ 
        {    
            printf("�����豸���㣬����ʧ��"); 
            return(false); 
        } 
    }

    t=equiptype[i].address;/* ȡ�������豸���豸���е���ʼ��ַ*/ 
    while(1) 
    {
/*��д��ҵ������Ժţ�״̬��Ϊ�ѷ���*/ 
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
}/*�豸���亯������*/ 

int reclaim (char *J,char *type) 
{ 
    int i,t,j,k,nn; 
    i=0; 
    while(i<n&&strcmp(equiptype[i].type,type)!=0) {
        i++; 
        if(i>=n)/*û���ҵ������豸*/ 
        { 
            printf("�޸����豸,�豸����ʧ��"); 
            return(false); 
        }
    }     
    t=equiptype[i].address; /*ȡ�������豸���豸���е���ʼ��ַ*/ 
    j=equiptype[i].count; /*ȡ�������豸������*/ 
    k=0; 
    nn=t+j; 
    for(;t<nn;t++) {
        if((strcmp(equipment[t].jobname,J) == 0) && (equipment[t].remain == 1)) 
        { 
            equipment[t].remain=0; 
            equipment[t].lnumber = 0; 
            strcpy(equipment[t].jobname,"");  //���job 
            k++; 
        }
    } 
    equiptype[i].remain= equiptype[i].remain+k;
    if(k==0) {
        printf("����ҵû��ʹ�ø����豸\n"); 
        return(false);
    }
    return 1;
}/*�豸���պ�������*/ 

int main()
{ 
    char J[4]; 
    int i,mm,a; 
    char type[10]; 
/*�豸�����ʼ����*/ 
    strcpy(equiptype[0].type,"input");/*�����*/ 
    equiptype[0].count=2; 
    equiptype[0].remain=2; 
    equiptype[0].address=0; 
    strcpy(equiptype[1].type,"printer");/*��ӡ�� */ 
    equiptype[1].count=3; 
    equiptype[1].remain=3; 
    equiptype[1].address=2; 
    strcpy(equiptype[2].type,"disk");/*���̻�*/ 
    equiptype[2].count=4; 
    equiptype[2].remain=4; 
    equiptype[2].address=5; 
    strcpy(equiptype[3].type,"tape");/*�Ŵ���*/ 
    equiptype[3].count=1; 
    equiptype[3].remain=1; 
    equiptype[3].address=9; 
    /*�豸����ʼ����*/ 
    for(i=0;i<10;i++){ 
        equipment[i].number=i; 
        equipment[i].status=1; 
        equipment[i].remain=0; 
    } 
    while(1) 
    { 
        printf("\n0���˳���1�����䣬2�����գ�3����ʾ"); 
        printf("\nѡ�����0~3��:"); 
        scanf("%d",&a); 
        switch(a) 
        { 
            case 0 : /*a=0�������*/ 
            exit(0); 
            case 1 : /*a=1�����豸*/ 
            printf("������ҵ������ҵ�����豸����豸��Ժ�"); 
            scanf("%s%s%d",J,type,&mm); 
            allocate(J,type,mm);/*�����豸*/ 
            break; 
            case 2: /*a=2�����豸*/ 
            printf("������ҵ������ҵ�黹���豸��"); 
            scanf("%s%s",J,type); 
            reclaim(J,type);/*�����豸*/ 
            break; 
            case 3: /*a=3 ����豸������豸��������*/ 
            printf("\n����豸���\n"); 
            printf(" �豸���� �豸���� ���к��豸\n"); 
            for(i=0;i<n;i++) 
                printf("%9s%8d%9d\n",equiptype[i].type,equiptype[i].count, equiptype[i].remain); 
                printf("����豸��:\n"); 
                printf("���Ժ� ��/�� ��/δ���� ռ����ҵ�� ��Ժ�\n"); 
            for(i=0;i<m;i++) 
                printf("%3d%8d%9d%12s%8d\n",equipment[i].number, equipment[i].status,equipment[i].remain,equipment[i].jobname,equipment[i].lnumber); 
        } 
    } 
}

