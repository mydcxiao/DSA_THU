#include<cstdio>
#define MAXSIZE 4000000
struct node{
	int data;
	 node *lc,*rc;	
};
int pre[MAXSIZE],post[MAXSIZE],i,j,k,m,n,e;//定义前序和后序数组 
node *ProperRebuild(int pre_lo,int pre_hi,int post_lo,int post_hi){//传入前序和后序递归范围 
	node *root=new node;//创建新节点 
	root->data=pre[pre_lo];//以新节点为根，数据域为前序最左端的数据 
	root->lc=root->rc=NULL;//其左右子树初始化为空 
	int pos,num_left;//定义前序左子树根在后序中的位置，左子树节点数 	
	if(post_lo==post_hi)return root;//若后序范围长度为0，返回当前根节点 
	for(i=post_lo;i<=post_hi;i++)//遍历给定范围的后序 
	if(post[i]==pre[pre_lo+1]){//若前序最左端+1即当前左子树根节点等于后序节点	
		pos=i;
		break;//记录左子树根节点在后序中的位置并退出循环 
	}
	num_left=pos-post_lo+1;//计算左子树节点数 
root->lc=ProperRebuild(pre_lo+1,pre_lo+num_left,post_lo,pos);//递归地在左子树中寻找当前节点的左孩子 
root->rc=ProperRebuild(pre_lo+num_left+1,pre_hi,pos+1,post_hi-1);//递归地在右子树中寻找当前节点的右孩子 
	return root;
}
void InTraverse(node *root){
	if(!root)return;
	InTraverse(root->lc);
	printf("%d ",root->data);
	InTraverse(root->rc);
}
int main(){
	scanf("%d",&n);
	for(i=0;i<n;i++)scanf("%d",&pre[i]);
	for(i=0;i<n;i++)scanf("%d",&post[i]);
	node *r=ProperRebuild(0,n-1,0,n-1);
	InTraverse(r);
	return 0;
}


// #pragma warning(disable:4996)
// #include<stdio.h>
// using namespace std;
// #define maxn 4000000
// int a[maxn], b[maxn], c[maxn], d[maxn],n;
// struct binnode {
// 	int data;
// 	binnode*lc, *rc, *parent;
// 	binnode() :data(0), lc(NULL), rc(NULL), parent(NULL) {}
// 	binnode(int e, binnode*p3 = NULL, binnode*p1 = NULL, binnode*p2 = NULL) :data(e), parent(p3), lc(p1), rc(p2) {}
// };
// class bintree {
// private:
// 	binnode * _root;
// 	int _size;
// public:
// 	bintree() :_size(0), _root(NULL) {}
// 	int size() { return _size; }
// 	binnode*root() { return _root; }
// 	binnode*insertaslc(binnode*p, int const&e);
// 	binnode*insertasrc(binnode*p, int const&e);
// 	binnode*insertasroot(int const&e);
// };
// binnode* bintree::insertaslc(binnode*p, int const&e)
// {
// 	binnode*p1 = new binnode(e, p);
// 	p->lc = p1;
// 	_size++;
// 	return p1;
// }
// binnode* bintree::insertasrc(binnode*p, int const&e)
// {
// 	binnode*p1 = new binnode(e);
// 	p->rc = p1;
// 	_size++;
// 	return p1;
// }
// binnode* bintree::insertasroot(int const&e)
// {
// 	_root = new binnode(e);
// 	_size = 1;
// 	return _root;
// }
// bintree tree;
// void creatright_tree(binnode*p, int lo3, int lo);
// //lo2,lo3这些都是坐标
// void creatleft_tree(binnode*p, int lo2)
// {
 
// 	auto t = tree.insertaslc(p, a[lo2]);
// 	auto lo3 = c[a[lo2]];
// 	if (lo3>0&&c[a[lo2]]>c[a[lo2+1]])//否则a[lo2+1]是右子树
// 	{
// 		creatleft_tree(t, ++lo2);
// 		creatright_tree(t, --lo3,lo2);
// 	}
// }
// void creatright_tree(binnode*p, int lo3,int lo)
// {
// 	auto t = tree.insertasrc(p, b[lo3]);
// 	auto lo2 = d[b[lo3]];
// 	if (lo3-c[a[lo]]>1)
// 	{
// 		creatleft_tree(t, ++lo2);
// 		creatright_tree(t, --lo3,lo2);
// 	}
// }
// void midtral(binnode*p)
// {
// 	if (!p)return;
// 	midtral(p->lc);
// 	if(p->data!=a[n-1])printf("%d ", p->data);
// 	else printf("%d\n",p->data);
// 	midtral(p->rc);
// }
// int main()
// {
// 	int lo1 = 0, lo2 = 0, lo3 = 0;//lo1是根的开始，lo2是左子树的开始，lo3是右子树的开始
// #ifndef _OJ_
// 	freopen("createtree.txt", "r", stdin);
// 	// freopen("trainout.txt", "w", stdout);
// #endif
// 	scanf("%d", &n);
// 	for (auto i = 0; i<n; i++)scanf("%d", &a[i]);
// 	for (auto i = 0; i<n; i++)scanf("%d", &b[i]);
// 	//使得可以根据值找到对应的坐标
// 	if(n<2){printf("%d\n", 1);return 0;}
// 	else{
// 	for (auto i = 1; i<n + 1; i++)c[b[i]] = i;//c是b的坐标
// 	for (auto i = 1; i<n + 1; i++)d[a[i]] = i;//d是a的坐标
// 	// for(auto i=1;i<n+1;i++)printf("%d\n",d[i]);
// 	auto root = tree.insertasroot(a[0]);
// 	creatleft_tree(root, 1);
// 	creatright_tree(root, --c[a[0]],1);
// 	midtral(root);}
// 	// auto right=b[n-2];
// 	// auto left=a[1];
// }

