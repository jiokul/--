#include <iostream>
#include <stdio.h>
#include <queue>
#include <string.h>
using namespace std;
typedef struct biao//表节点
{
    int adjvex;//该弧所指向的定点的位置
    biao *next;
}biao;

typedef struct tou//头结点
{
    char data[20];//编号
    biao *firstdian;//第一个表结点的地址，指向第一条依附该顶点的弧的指针
}to,ad[20];

typedef struct shuju
{
    ad ver;
    int nd,nb;
}shuju;

int chazhao(shuju g,char u[])//返回顶点u在图中的位置
{
    int i;
    for(i=0;i<20;i++)
    {
        if(strcmp(g.ver[i].data,u)==0)
        {
            return i;
        }
    }
    return -1;
}

void creat(shuju &g,char a[][20],int dian,int bian)//构造有向图
{
    g.nb=bian;
    g.nd=dian;
    int i,j,k;
    char v1[20],v2[20];
    for(i=0;i<g.nd;i++)
    {
        strcpy(g.ver[i].data,a[i]);
        g.ver[i].firstdian=NULL;
    }
    cout<<"请输入边(示例：A B,表示A指向B)"<<endl;
    for(i=0;i<g.nb;i++)
    {
        cin>>v1>>v2;
        k=chazhao(g,v1);
        j=chazhao(g,v2);
        biao *p=new biao;
        p->adjvex=j;
        p->next=g.ver[k].firstdian;
        g.ver[k].firstdian=p;
    }

}

void rudu(shuju g,int ru[])//各定点的入度计算
{
    int i;
    for(i=0;i<g.nd;i++)
    {
        ru[i]=0;
    }
    for(i=0;i<g.nd;i++)
    {
        biao *p=g.ver[i].firstdian;
        while(p)
        {
            ru[p->adjvex]++;
            p=p->next;
        }
    }
}

int tupu(shuju g,int b[])//拓扑排序，判断是否存在回路
{
    queue<int>qu;
    int ru[g.nd]={0};//入度数组
    int i;
    int count=0;//计入队次数

    rudu(g,ru);

    for(i=0;i<g.nd;i++)//入度为0的点入队
    {
        if(ru[i]==0)
        {
            qu.push(i);
        }
    }
    while(!qu.empty())
    {
        int v=qu.front();
        b[v]=1;
        qu.pop();
        count++;
        cout<<g.ver[v].data<<" ";
        biao *p=g.ver[v].firstdian;
        while(p)//改顶点出队后，所有以该边为入的顶点入度减一
        {
            if((--ru[p->adjvex])==0)
                qu.push(p->adjvex);//顶点入度减一后为0，进入队列
            p=p->next;
        }
    }
    //判断不同情况，根据返回值判断是否存在回路
    if(count<g.nd)
        return 1;
    if(count==g.nd)
        return 0;
    if(count>g.nd)
        return -1;
}
int main()
{
    int dian,bian;
    char a;
    char d[20][20];
    char m[20][20];
    int jilu[20]={0};
    int i,j;
    cout<<"请输入定点数目和边数目"<<endl;
    cin>>dian>>bian;
    cout<<"请输入定点编号和名称(示例：A 数据结构)"<<endl;
    for(i=0;i<dian;i++)
    {
        scanf("%S",d[i]);
        scanf("%s",m[i]);
    }
    shuju g;
    creat(g,d,dian,bian);
    cout<<"拓扑排序为:";
    j=tupu(g,jilu);
    cout<<endl;
    if(j==0)
    {
        cout<<"无回路,课表通过"<<endl;
    }
    if(j==1)
    {
        cout<<"有回路,出现错误的部分是:"<<endl;
        for(i=0;i<g.nd;i++)
        {
            if(jilu[i]==0)
            {
                printf("%s %s\n",d[i],m[i]);
            }
        }
    }
    if(j==-1)
    {
        cout<<"程序运行出现错误,请调试";
    }

    return 0;
}
