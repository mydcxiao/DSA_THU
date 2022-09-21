#include<cstdio>
#define MAXSIZE 1000000
#define GetMax(a,b) a>b?a:b
//注意全局变量数组的元素都会自动初始化为0 
struct ENode{
	int vsub;
	ENode *succ;
};
struct VNode{
	int in,len;//相对于邻接表结构，额外添加了属性len以计算到每个顶点的最大路径 
	ENode *fstEdge;	
};
VNode adjList[MAXSIZE];ENode *t;
int visited[MAXSIZE],stack[MAXSIZE],top=0,maxlen=0,n,e,i,j;
void TSort(){
	for(int k=0;k<n;k++)if(!adjList[k].in)stack[++top]=k;
	while(top){
		int v=stack[top--];
		for(ENode *p=adjList[v].fstEdge;p;p=p->succ){	
		//策略：动态规划-不断的更新到每个入度为0的顶点的邻居的最大路径长度
//相对于拓扑排序，额外添加了下述2句以更新到每个邻居的最大路径长度和记录图的最大路径长度 
			adjList[p->vsub].len=GetMax(adjList[v].len+1,adjList[p->vsub].len);
			maxlen=GetMax(adjList[p->vsub].len,maxlen);
			if(!(--adjList[p->vsub].in))stack[++top]=p->vsub;
		}
	}	
}
int main(){
	scanf("%d%d",&n,&e);
	for(int k=0;k<e;k++){
		scanf("%d%d",&i,&j);i--;j--;
		t=new ENode;t->vsub=j;adjList[j].in++;
		t->succ=adjList[i].fstEdge;adjList[i].fstEdge=t;
	}
	TSort();printf("%d\n",maxlen+1);//最后求的是最大路径包含的顶点数，故需要+1 
	return 0;
}

// #pragma warning(disable:4996)
// #include<stdio.h>
// using namespace std;
// #define maxn 1000001
// int maxx;
// struct listnode
// {
// 	listnode*pre;
// 	int indu_num = 0;//记录indu指向的j,即i->j
// 	listnode() {}
// 	listnode(int n, listnode*p = NULL) :indu_num(n), pre(p) {}
// };
// struct p_list
// {
// 	listnode*head, *trail;
// 	int flag = 1,length=1;
// 	void init();
// 	// ~p_list();
// 	p_list() { init(); }
// 	void insert(int&out);
// 	// p_list&operator=(p_list&a);
// };
// void p_list::init()
// {
// 	head = new listnode();
// 	trail = new listnode();
// 	head->pre = trail;
// 	trail->pre = NULL;
// }
// void p_list::insert(int&out)//越先进入的元素，越靠近队尾
// {
// 	listnode*p = new listnode(out);
// 	p->pre = head->pre;
// 	head->pre = p;
// }
// p_list edge[maxn];
// int dsf(listnode*p, int i)//i是上一层的值
// {
// 	auto q = p->pre;
// 	int count=1;
// 	while (q != edge[i].trail)
// 	{
// 		if(edge[i].flag==0){
// 			count+=edge[i].length;break;
// 		}
// 		count+=dsf(edge[q->indu_num].head, q->indu_num);
// 		if (edge[i].length >count);//最开始为1，后来为每个出边返回值+1,count=1就从来没变过
// 		else edge[i].length = count;
// 		q = q->pre;
// 		count=1;
// 	}
// 	edge[i].flag = 0;
// 	if (maxx>edge[i].length);
// 	else maxx = edge[i].length;
// 	return edge[i].length;
// }
// void travel(int n)
// {
// 	int count = 1;
// 	maxx = count;
// 	for (auto i = 0; i<n; i++)
// 	{
// 		if (edge[i].flag == 0);
// 		else {
// 			auto p = edge[i].head;
// 			dsf(p, i);
// 		}
// 	}
// }
// int main()
// {
// #ifndef _OJ_
// 	freopen("travelin.txt", "r", stdin);
// 	// freopen("travelout.txt", "w", stdout);
// #endif
// 	int i, j, m, n;//i,j是边的坐标,cap是边的总数
// 	scanf("%d %d", &n, &m);//m是有效边的数目，n是点的个数
// 	while (m--) {
// 		scanf("%d %d", &i, &j);
// 		edge[i - 1].insert(--j);
// 	}
// 	travel(n);
// 	printf("%d\n", maxx);
// }

