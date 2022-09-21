//没有对二叉堆进行封装，因为没有必要
#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<string.h>
#define maxn 4294967295//2^32-1
#define task_num 4000000
#define print_num 2000000
#define Parent(i) ((i-1)>>1)
#define Lchild(i) ((i<<1)+1)
#define Rchild(i) ((i+1)<<1)
#define valid(i,n) (i>0&&i<n)
using namespace std;
struct element_heap {
	long long int priority;
	char num_c[9];
	element_heap&operator=(const element_heap&a)
	{
		priority = a.priority;
		strcpy(num_c, a.num_c);
		return*this;
	}
};
bool operator<(const element_heap&a,const element_heap&b)
{
	if (a.priority < b.priority)return true;
	else if (a.priority == b.priority)
	{
		if (strcmp(a.num_c, b.num_c) < 0)return true;
		else return false;
	}
	else return false;
}
element_heap task_queue[task_num];
int n = 0;//n代表数组长度;
char print_queue[print_num][9];
//long long int print_priority[print_num];
void swap(int i, int j)
{
	auto temp = task_queue[i];
	task_queue[i] = task_queue[j];
	task_queue[j] = temp;
	//printf("111\n");
}
//以下函数作用的对象就只有task_queue这一个数组;
//上滤
void percolateUp(int i)
{
	auto temp = task_queue[i];
	while (i > 0) {
		int j = Parent(i);
		if (temp < task_queue[j]) {
			task_queue[i] = task_queue[j];
			i = j;
		}
		else {
			task_queue[i] = temp;
			break;
		}
	}
	if (i == 0)task_queue[i] = temp;
}
int min_in_three(int i)
{
	auto lc = Lchild(i);
	//printf("lc=%d\n", lc);
	auto rc = Rchild(i);
	int min;
	if (valid(lc, n) && task_queue[lc] < task_queue[i])min = lc;
	else min = i;
	if (valid(rc, n) && task_queue[rc] < task_queue[min])min = rc;
	return min;
}
//下滤
void percolateDown(int i)
{
	int j = 0;
	while (i != (j = min_in_three(i)))
	{
		swap(i, j);
		i = j;
	}
}
//建堆
void Floyd()//n是数组长度
{
	int count = 0;
	for (auto i = Parent(n - 1); i >= 0; i--) { percolateDown(i); }
}
//插入
void insert(element_heap a) {
	if (a.priority >maxn)return;
	task_queue[n++] = a;
	percolateUp( n- 1);
}
element_heap del_min()
{
	auto t = task_queue[0];
	task_queue[0] = task_queue[--n];
	percolateDown(0);
	t.priority *= 2;
	return t;
}
int main()
{
#ifndef _OJ_
	freopen("ADT.txt", "r", stdin);
	// freopen("travelout.txt", "w", stdout);
#endif
	int m,len=-1,count=0;
	scanf("%d %d", &n, &m);
	while (++len<n) {
		scanf("%lld %s", &(task_queue[len].priority), &(task_queue[len].num_c));
	}
	Floyd();
	for (auto i = 0; i < m&&n>0; i++)
	{
		auto t = del_min();
		strcpy(print_queue[i],t.num_c);
		insert(t);
		count++;
	}
	for (auto i = 0; i < count; i++)printf("%s\n",print_queue[i]);
}

