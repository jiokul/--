include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;
typedef struct shuju
{
    char dingdian[20][20];//定点存储
    char mingcheng[20][20];//定点名称
    int bian[20][20];//边矩阵
    int nb;//边数目
    int nd;//顶点数目
    int flag;//是否存在环的判断值
}shuju;

int jilu[20];

void creat(shuju &g)//构造有向图
{
    g.flag=0;
    cout<<"请输入定点数目和边数目(示例6 8(6为定点数，8为边数目))"<<endl;
    cin>>g.nd>>g.nb;
    cout<<"请输入定点编号和名称(示例：A 数据结构)"<<endl;
    int i,j,k;
    for(i=0;i<g.nd;i++)
    {
        scanf("%s",g.dingdian[i]);
        scanf("%s",g.mingcheng[i]);
    }
    for(i=0;i<g.nd;i++)
    {
        for(j=0;j<g.nd;j++)
        {
            g.bian[i][j]=0;
        }
    }
    cout<<"请输入边(示例：A B,表示A指向B)"<<endl;
    char v1[20],v2[20];
    for(k=0;k<g.nb;k++)
    {
        cin>>v1>>v2;
        for(i=0;i<g.nd;i++)
        {
            if(strcmp(v1,g.dingdian[i])==0)
                break;
        }
        for(j=0;j<g.nd;j++)
        {
            if(strcmp(v2,g.dingdian[j])==0)
                break;
        }
        g.bian[i][j]=1;
    }
}

void DFS(int i,shuju &s)//深度遍历，判断是否存在环
{
    jilu[i]=1;
    int j;
    for(j=0;j<s.nd;j++)
    {
        if(s.bian[i][j]!=0)//如果当前结点有指向的结点
        {
            if(jilu[j]==1)//并且已经被访问过
            {
                s.flag=1;//有环
                break;
            }
            else
            {
                if(jilu[j]==-1)//当前结点后边的结点都被访问过，直接跳至下一个结点
                    continue;
                else
                    DFS(j,s);//否则递归访问
            }

        }
    }
    jilu[i]=-1;
}
int main()
{
    shuju s;
    creat(s);
    int i;
    for(i=0;i<s.nd;i++)
    {
        if(jilu[i]==-1)
            continue;
        DFS(i,s);
        if(s.flag==1)
        {
            cout<<"有回路,出现错误"<<endl;
            break;
        }
    }
    if(s.flag==0)
    {
        cout<<"无回路,课表通过"<<endl;
    }
    return 0;
}

