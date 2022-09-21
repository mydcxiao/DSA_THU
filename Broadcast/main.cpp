#include<iostream>
#define MAXSIZE 10001
#define UNDISCOVERED 0
#define DISCOVERED 1
#define VISITED 2
using namespace std;
struct EdgeNode{
	int vsub;
	EdgeNode* succ;	
};
struct VertexNode{
	EdgeNode* fstEdge;	
};
VertexNode adjList[MAXSIZE];
int queue[MAXSIZE],status[MAXSIZE],front=0,rear=0,i,j,k,m,n;//注意全局数组元素自动初始化为0 
int BFS(int v){
	queue[rear]=v;rear=(rear+1)%MAXSIZE;
	status[v]=DISCOVERED;//当前顶点已发现，入队 
	while(front!=rear){
		v=queue[front];front=(front+1)%MAXSIZE;
		for(EdgeNode* e=adjList[v].fstEdge;e;e=e->succ)
		switch(status[e->vsub]){
			case UNDISCOVERED:queue[rear]=e->vsub;rear=(rear+1)%MAXSIZE;
				status[e->vsub]=DISCOVERED;break;//访问队外未发现的邻居，则入队 
			case DISCOVERED:return -1;//访问队中已发现的邻居，则失败 
		}//若访问已访问的顶点，则忽略 
		status[v]=VISITED;//当前顶点访问完毕 
	}
	return 1;
}
int main(){
	cin>>n>>m;
	while(m--){//创建无向图 
		cin>>i>>j;
		EdgeNode* t=new EdgeNode;t->vsub=j;
		t->succ=adjList[i].fstEdge;adjList[i].fstEdge=t;
		t=new EdgeNode;t->vsub=i;
		t->succ=adjList[j].fstEdge;adjList[j].fstEdge=t;
	}cout<<BFS(1);//因为是无向图，不需从多个可能的顶点出发，只需从一个顶点出发即可遍历全图 
	return 0;
}

// #pragma warning(disable:4996)
// #include<stdio.h>
// using namespace std;
// #define maxn 10000
// #define Flag(i)((i==1)?2:1)
// struct listnode
// {
//     listnode*pre;
//     int num = -1;//记录该节点的编号
//     listnode() {}
//     listnode(int n, listnode*p = NULL) :num(n), pre(p) {}
// };
// struct p_list
// {
//     listnode*head, *trail;
//     int flag = 0;
//     int visit = 0;
//     void init();
//     p_list() { init(); }
//     void insert(int&out);
// };
// void p_list::init()
// {
//     head = new listnode();
//     trail = new listnode();
//     head->pre = trail;
//     trail->pre = NULL;
// }
// void p_list::insert(int&num)//越先进入的元素，越靠近队尾
// {
//     listnode*p = new listnode(num);
//     p->pre = head->pre;
//     head->pre = p;
// }
// p_list country[maxn];
// int Queue[maxn];
// int hi=0,result=1,trail=0;
// void bsf(int pos)
// {
//     if(country[Queue[hi]].visit == 0)
//     {
//         auto p = country[pos].head->pre;
//          while (p != country[pos].trail)
//     {
//         if(country[p->num].flag==0)country[p->num].flag = Flag(country[pos].flag);
//         else if(country[p->num].flag == Flag(country[pos].flag));
//         else{result=-1;break;}
//         Queue[hi++]=p->num;
//         p=p->pre;
//     }
//     country[pos].visit=1;
//     }
//     if(hi>0)
//     bsf(Queue[--hi]);
 
// }
// void travel(int n, int m)
// {
//     country[0].flag = 1;
//     for (auto i = 0; i<n&&result>0; i++)
//     {
//         Queue[0]=i;
//         bsf(i);
//     }
// }
// int main()
// {
// #ifndef _OJ_
//     freopen("bfs.txt", "r", stdin);
//     // freopen("travelout.txt", "w", stdout);
// #endif
//     int i, j, m, n;
//     scanf("%d %d", &n, &m);
//     auto t = m;
//     while (t--) {
//         scanf("%d %d", &i, &j);
//         country[i - 1].insert(--j);
//         country[j].insert(--i);
 
//     }
//     for (auto i = 0; i<n; i++)country[i].flag = 0;
//     travel(n, m);
//     printf("%d\n", result);
// }

