#pragma warning(disable:4996)
#include <stdio.h>
#include "temperature.h"
#define maxn 50000
using namespace std;
struct range_node;//范围查询的节点构成范围查询树
//station_type是每一个观测站的具体内容（包括了x,y坐标，温度temp，
//观测站内部还有一个指针c，是用来指向叶子节点，然后用来回溯路径）
//一个指针road，用来指向前一个节点
typedef struct _station_type
{
	int x, y;
	int temp;
	_station_type&operator=(const _station_type&data)
	{
		temp = data.temp;
		x = data.x;
		y = data.y;
		return *this;
	}
	range_node*c,*road=NULL;
} station_type;
station_type stations[maxn];
//fctree是用来构建y值数组，每个fctree中都含有station_type类型的data
//y值比较大小，当y值相同时，看x值，这里不可能出现x与y值相同
struct fctree {
	station_type data;
	bool operator>(const fctree&a)
	{
		if (data.y > a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x > a.data.x)return true;
			else return false;
		}
		else return false;
	}
	bool operator<(const fctree&a)
	{
		if (data.y < a.data.y)return true;
		else if (data.y == a.data.y) {
			if (data.x < a.data.x)return true;
			else return false;
		}
		else return false;
	}
};
//每个节点都有左右指针和对应的y值
//首先要构建AVL树
struct range_node {
	range_node*rc, *lc, *parent;
	fctree*fc;//这个指针用于指向y数值的数组，记得初始化时要用new fc来确定它的数组大小
	int fc_size = 0;
	station_type data;//每个节点中都只有一个数据点
	int height = 0;
	range_node() { rc = lc = NULL; fc = NULL; parent = NULL; }
	range_node(const station_type&e, range_node*p, fctree*fc1 = NULL, range_node*lc1 = NULL, range_node*rc1 = NULL) :data(e), parent(p), fc(fc1), lc(lc1), rc(rc1) {}
};
 
//构建AVL树---------------------------------------------------------
struct rangetree {
	//所包含的数据成员;
	rangetree() { range_node(); }
	range_node*_hot;//待插入点的父亲节点
	range_node*_root;//根节点
	range_node*&search(const int&e);
	void insertAsRoot(const station_type&e);
	range_node*insert(const station_type&data);
	range_node*&fromparento(range_node*g);
	range_node*connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3);
	range_node*rotateAt(range_node*g);
	void search_leaf(range_node*&v, int&i, range_node*hot);
	int size = 0;
};
//_station_type的相等是要求x和y都相等
bool operator==(const _station_type&data1, const _station_type&data2)
{
	return ((data1.x == data2.x) && (data1.y == data2.y));
}
int stature(range_node*a) { return a ? a->height : -1; }//由于a可能为空，因此需要单独给它一个函数
void rangetree::insertAsRoot(const station_type&e)
{
	_root = new range_node(e, NULL); size++;
}
range_node*&searchin(range_node*&v, const int&e, range_node*&hot)
{
	if (!v)return v;
	hot = v;
	return searchin((e <= v->data.x) ? v->lc : v->rc, e, hot);
}
range_node*&rangetree::search(const int&e)
{
	//有了_hot=NULL后，就不用每次查询都把_hot重新更新了
	return searchin(_root, e, _hot = NULL);
}
bool Balance(range_node a) { return (stature(a.lc) - stature(a.rc)) > -2 && stature(a.lc) - stature(a.rc) < 2; }
bool islchild(range_node*g) { return g->parent && (g->parent->lc == g); }
bool isrchild(range_node*g) { return g->parent && (g->parent->rc == g); }
void updateheight(range_node*g)
{
	if (stature(g->lc)>stature(g->rc)) { g->height = stature(g->lc) + 1; }
	else { g->height = stature(g->rc) + 1; }
}
range_node*tallerchild(range_node*g)
{
	return (stature(g->lc) > stature(g->rc)) ? g->lc : (((stature(g->lc) <stature(g->rc)) ? g->rc : (islchild(g) ? g->lc : g->rc)));
}
range_node*&rangetree::fromparento(range_node*g)
{
	if (g->parent) { return islchild(g) ? g->parent->lc : g->parent->rc; }
	else { return _root; }
}
range_node*rangetree::insert(const station_type&data)
{
	range_node*&x = search(data.x);
	//x不能改变，因为x是引用，x改变，则其父节点的孩子指针也跟着改变，故为了安全起见，不能改变；
	range_node*xx = x = new range_node(data, _hot);
	for (range_node*g = _hot; g; g = g->parent)
	{
		if (!Balance(*g)) {
			auto&temp = fromparento(g);//=rotateAt(tallerchild(tallerchild(g)));
									   //auto p = tallerchild(g);
									   //auto v = tallerchild(p);
			temp = rotateAt(tallerchild(tallerchild(g)));
			break;
		}
		else updateheight(g);
	}
	size++;
	return xx;
}
range_node*rangetree::connect34(range_node*a, range_node*b, range_node*c, range_node*t0, range_node*t1, range_node*t2, range_node*t3)
{
	a->lc = t0; if (t0) { t0->parent = a; }// printf("a->lc= %d\n", a->lc->data.x);
	a->rc = t1; if (t1) { t1->parent = a; }//printf("a->rc= %d\n", a->rc->data.x);
	updateheight(a);
	c->lc = t2; if (t2) { t2->parent = c; } //printf("c->lc= %d\n", c->lc->data.x);
	c->rc = t3; if (t3) { t3->parent = c; }// printf("c->rc= %d\n", c->rc->data.x);
	updateheight(c);
	b->lc = a; a->parent = b;
	b->rc = c; c->parent = b; updateheight(b);
	return b;
}
range_node*rangetree::rotateAt(range_node*v)
{
	range_node*p = v->parent;
	range_node*g = p->parent;
	if (islchild(p)) {
		if (islchild(v)) {
			p->parent = g->parent;//别忘了parent指针也要记得更新！
			return connect34(v, p, g, v->lc, v->rc, p->rc, g->rc);
		}
		else
		{
			v->parent = g->parent;
			return connect34(p, v, g, p->lc, v->lc, v->rc, g->rc);
		}
	}
	else {
		if (islchild(v)) {
			v->parent = g->parent;
			return connect34(g, v, p, g->lc, v->lc, v->rc, p->rc);
		}
		else {
			p->parent = g->parent;
			return connect34(g, p, v, g->lc, p->lc, v->lc, v->rc);
		}
	}
}
//AVL树构建完毕---------------------------------------------------------
 
bool isleaf(range_node*root) {
	return root && (!root->lc && !root->rc);
}
int n;
long long int  record = 0;
int count;
station_type stack_x1[100], stack_x2[100];
int road_x1, road_x2;
void merge_y(fctree*&a1, fctree data_lc[], fctree data_rc[], int n_lc, int n_rc)
{
	a1 = new fctree[n_lc + n_rc];
	int i = 0, j = 0, k = 0;
	while (i < n_lc&&j < n_rc)
	{
		if (data_lc[i] < data_rc[j])a1[k++].data = data_lc[i++].data;
		else a1[k++].data = data_rc[j++].data;
	}
	if (i == n_lc)
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_rc[j++].data;
		}
	else
		while (k<n_lc + n_rc)
		{
			a1[k++].data = data_lc[i++].data;
		}
}
//查找叶子节点并且插入对应的x值节点，注意，每插完一次，每个节点的y值也会更新一次
//节点用fctree装y值
void rangetree::search_leaf(range_node*&v, int&i, range_node*hot)
{
	if (!v) {
		if (i < n)
		{
			stations[i].c = v = new range_node(stations[i], hot);
			v->fc = new fctree[1]; 
			v->fc->data = stations[i++];
			(v->fc_size)++;
		}
	}
	else {
		hot = v;
		search_leaf(v->lc, i, hot);
		search_leaf(v->rc, i, hot);
		if (v->lc && v->rc)
		{
			merge_y(v->fc, v->lc->fc, v->rc->fc, v->lc->fc_size, v->rc->fc_size);
			v->fc_size = v->lc->fc_size + v->rc->fc_size;
		}
		else
		{
			v->fc = new fctree[v->lc->fc_size];
			for (auto i = 0; i < v->lc->fc_size; i++)v->fc[i].data = v->lc->fc[i].data;
			v->fc_size = v->lc->fc_size;
		}
	}
}
//用于对x进行2分查找
void merge_x(station_type data[], int lo, int mi, int hi)
{
	station_type*a1 = new station_type[mi - lo];
	int k = lo, i = 0, t = mi - lo;
	for (auto i = 0; i < mi - lo; i++)a1[i] = data[k++];
	while ((mi< hi) && (i<t))
	{
		if (a1[i].x < data[mi].x)data[lo++] = a1[i++];
		else if (a1[i].x == data[mi].x&&a1[i].y < data[mi].y)data[lo++] = a1[i++];
		else data[lo++] = data[mi++];
	}
	if (i == t);
	else while (lo < hi)data[lo++] = a1[i++];
	delete[]a1;
}
void mergesort_x(station_type data[], int lo, int hi)
{
	int mi;
	if (hi - lo > 1) {
		mi = (hi + lo) >> 1;
		mergesort_x(data, lo, mi);
		mergesort_x(data, mi, hi);
		merge_x(data, lo, mi, hi);
	}
	else return;
}
//寻找x1和x2
void search_x1(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x<x1) ? lo = mi + 1 : hi = mi;
	}
	if (lo<lenght&& stations[lo].x <= x2) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
			
		}
	}
	else;
}
void search_x2(range_node*root, int x1, int x2, station_type stack[], int&road, int lo, int hi)
{
	int lenght = hi;
	while (hi > lo)
	{
		int mi = (hi + lo) >> 1;
		(stations[mi].x > x2) ? hi = mi : lo = mi + 1;
	}
	--lo;
	if (lo > -1 && stations[lo].x >= x1) {
		auto root = stations[lo].c;
		while (root)
		{
			stack[road] = root->data;
			stack[road].c = root;
			if (!isleaf(stack[road].c))stack[road].road = stack[road - 1].c;
			road++;
			root = root->parent;
		}
	}
	else;
}
//寻找每条路径的公共节点，从该节点开始回溯
range_node*common_root()
{
	while (0 < road_x1 && 0 < road_x2&&stack_x1[--road_x1] == stack_x2[--road_x2]);
	return (stack_x1[road_x1] == stack_x2[road_x2]) ? stack_x1[road_x1].c : stack_x1[++road_x1].c;
}
//对每个节点的y值进行2分查找！
void search_y(range_node*root, int lo, int hi, int y1, int y2)
{
	while (lo < hi)
	{
		int mi = (lo + hi) >> 1;
		(y1 <= root->fc[mi].data.y) ? hi = mi : lo = mi + 1;
	}
	while (lo < root->fc_size&&root->fc[lo].data.y <= y2  )
	{
		record += root->fc[lo].data.temp;
		count++;
		lo++;
	}
}
void travelReport(int x1,int x2,int y1, int y2)
{
	while (road_x1 >= 0)
	{
		auto rc = stack_x1[road_x1].c->rc;
		auto lc = stack_x1[road_x1].c->lc;
		auto road = stack_x1[road_x1].road;
		if (rc&&rc!=road)search_y(rc, 0, rc->fc_size, y1, y2);
		road_x1--;
	}
	auto now = stack_x1[road_x1 + 1].c;
	if (now->data.x >= x1 &&now->data.x <= x2 && now->data.y >= y1 && now->data.y <= y2)
	{
		count++;
		record += now->data.temp;
	}
	while (road_x2 >= 0)
	{
		auto rc = stack_x2[road_x2].c->rc;
		auto lc = stack_x2[road_x2].c->lc;
		auto road = stack_x2[road_x2].road;
		if (lc&&lc != road)search_y(lc, 0, lc->fc_size, y1, y2);
		road_x2--;
	}
	auto now2 = stack_x2[road_x2 + 1].c;
	if (now2->data.x >= x1 && now2->data.x <= x2 && now2->data.y >= y1 && now2->data.y <= y2)
	{
		count++;
		record += now2->data.temp;
	}
}
//先序和中序遍历用来保证AVL树的正确构建-----------------------------------------------------------------
void xianxutravel(range_node*r)
{
	printf("%d(%d)\n", r->data.x, r->data.y);
	if (r->lc)xianxutravel(r->lc);
	if (r->rc)xianxutravel(r->rc);
}
void midtravel(range_node*r)
{
	if (r->lc)midtravel(r->lc);
	printf("%d(%d)\n", r->data.x, r->data.y);
	if (r->rc)midtravel(r->rc);
}
int main()
{
	n = GetNumOfStation();
	if (n == 0) {
		int x1, x2, y1, y2;
		while (GetQuery(&x1, &y1, &x2, &y2)) {
			Response(0); printf("0\n");
		}
		return 0;
	}
	rangetree a;
	for (auto i = 0; i < n; i++)GetStationInfo(i, &(stations[i].x), &(stations[i].y), &(stations[i].temp));
	a.insertAsRoot(stations[0]);
	for (auto i = 1; i < n; i++)a.insert(stations[i]);
	//为了防止出现先大的插入导致后面小的没有位置，所以得先排序;
 
	mergesort_x(stations, 0, n);
	int i = 0;
	a._hot = NULL;
	a.search_leaf(a._root, i, a._hot);
	//先序和中序遍历
	//midtravel(a._root);
	//printf("--------------\n");
	//xianxutravel(a._root);
	
	int x1, x2, y1, y2, num = 1;
	while (GetQuery(&x1, &y1, &x2, &y2))
	{
		search_x1(a._root, x1, x2, stack_x1, road_x1, 0, n);
		//取消注释可以看到路径
		//printf("road%d:= ", num);
		//for (auto i = 0; i < road_x1; i++) { printf("%d(%d) ", stack_x1[i].x, stack_x1[i].y); }
		//printf("\n");
		search_x2(a._root, x1, x2, stack_x2, road_x2, 0, n);
		//printf("road%d:= ", num++);
		//printf("%d,%d\n", road_x1, road_x2);
		//for (auto i = 0; i < road_x2; i++) { printf("%d(%d) ", stack_x2[i].x, stack_x2[i].y); }
		//printf("\n");
		int t1 = road_x1, t2 = road_x2;
		if (road_x1&&road_x2)
		{
			range_node*v = common_root();
			//取消注释可以看到公共节点
			//printf("%d,%d\n", road_x1, road_x2);
			//printf("v= %d(%d)\n", v->data.x, v->data.y
				road_x1--;
				travelReport(x1,x2,y1, y2);
			//printf("count = %d\n", count);
			if (count != 0) {
				Response(record / count);
				//取消注释可以直接看到输出
				//printf("%d\n", record / count);
				//printf("count= %d\n", count);
			}
			else {
				Response(0);
				//printf("0\n");
			}
		}
		else {
			Response(0);
			//printf("0\n");
		}
		for (auto i = 0; i < t1; i++) { stack_x1[i].c = NULL; stack_x1[i].road = NULL; stack_x1[i].x = 0; stack_x1[i].y = 0; stack_x1[i].temp = 0; }
		for (auto i = 0; i <t2; i++) { stack_x2[i].c = NULL; stack_x1[i].road = NULL; stack_x2[i].x = 0; stack_x2[i].y = 0; stack_x2[i].temp = 0; }
		t1 = t2 = road_x1 = road_x2 = record = count = 0;
	}
}

