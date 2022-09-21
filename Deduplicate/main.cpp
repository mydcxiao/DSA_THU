#include<cstdio>
#include<cstring>
#define HASHSIZE 600001
using namespace std;
struct Slot {//每个桶对应的槽位，存储冲突，即映射到同一地址且不重复的字符串（实则字符指针） 
	char* data;//数据项，存储字符指针 
	bool repeat;//标志，判别字符串是否重复
	Slot* succ;//后继 
}buckets[HASHSIZE];//桶数组（散列表） 
char name[HASHSIZE][41];//字符二维数组（必须开头定义），存储输入字符串，注意二维长度为40+1个结束符=41 
void Insert(int addr, char* s) {//在相应地址中插入冲突的字符串（实则字符指针） 
	Slot* t = new Slot;
	t->data = s; t->repeat = false;//初始化当前字符串从未重复 
	t->succ = buckets[addr].succ;//链表头插法 
	buckets[addr].succ = t;
}
int HashCode(char* s) {//散列码转换（字符串转数字） 
	int sum = 0, len = strlen(s);
	for (int i = 0; i<len; i++)//多项式求和 
		sum += (i + 1)*(s[i] - 'a'+1);
	return sum;
}
int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; i++){		
		scanf("%s", name[i]);
		int addr = HashCode(name[i]) % HASHSIZE;//获得映射到的地址 
		Slot* p = buckets[addr].succ;//从当前桶的第1个槽位开始 
		while (p)//遍历所有槽位（冲突的单元） 
		if (!strcmp(p->data, name[i])) {//若当前槽位的字符串重复 
			if (!p->repeat) {//检查当前槽位的字符串是否重复
				p->repeat = true;//若未重复，则标志为已重复过 
				puts(name[i]);//输出重复字符串 
			}break;//若重复过，则忽略，无论是否重复过，皆终止遍历 
		}
		else p = p->succ;
		if (!p)Insert(addr, name[i]);//若当前槽位空，则进行插入 
	}
	return 0;
}

// #define _CRT_SECURE_NO_DEPRECATE
// #include<stdio.h>
// #include<string.h>
// #define maxn 799999
// using namespace std;
// struct result {
// 	int bool_value;
// 	int chongfu;
// };
// //节点是指节点内容
// struct listnode{
// 	listnode*pre, *succ;
// 	char*meal_name;
// 	int chongfu = -1;
// 	listnode(){}
// 	listnode(char*a,listnode*p1=NULL,listnode*p2=NULL):meal_name(a),pre(p1),succ(p2){}
// };
// //列表是包括多个节点的组合
// int count = 0;
// struct list {
// 	listnode*head, *tail;
// 	list() { init(); }
// 	void init()
// 	{
// 		head = new listnode;
// 		tail = new listnode;
// 		head->pre = NULL; head->succ = tail;
// 		tail->pre = head; tail->succ = NULL;
// 	}
// 	//每一个新节点都插入到head之后
// 	void insert_head(char*mealnm)
// 	{
// 		auto p = new listnode(mealnm);
// 		p->succ = head->succ;
// 		head->succ->pre = p;
// 		p->pre = head;
// 		head->succ = p;
// 	}
// 	void insert_tail(char*mealnm)
// 	{
// 		auto p = new listnode(mealnm);
// 		p->pre = tail->pre;
// 		tail->pre->succ = p;
// 		p->succ = tail;
// 		tail->pre = p;
// 	}
// 	result check_rpt1(char*mealnm);
// };
// char meal[600000][41];
// list list_hash[maxn];
// list rept_hash;
// result list::check_rpt1(char*mealnm)
// {
// 	auto p = this->head;
// 	result t;
// 	while ((p=p->succ) != this->tail)
// 	{
// 		if (strcmp(p->meal_name, mealnm)==0)
// 		{
// 			t.bool_value = 0;
// 			t.chongfu=++p->chongfu;
// 			return t;
// 		}
// 	}
// 	t.bool_value = 1;
// 	t.chongfu = 0;
// 	return t;
// }
// int hashcode(char be_hash[40])
// {
// 	int length= strlen(be_hash);
// 	int num = 0;
// 	for (auto i = 0; i < length; i++)
// 	{
// 		num += (be_hash[i] - 96)*(i+1);
// 	}
// 	return num;
// }
// int main()
// {
// #ifndef _OJ_
// 	freopen("reptmealin.txt", "r", stdin);
// #endif
// 	int n,num,list_location,rept_num=0;
// 	scanf("%d", &n);
// 	for (auto i = 0; i < n; i++)
// 	{
// 		scanf("%s", meal[i]);
// 		num = hashcode(meal[i]);
// 		list_location = num % maxn;
// 		int lenght = strlen(meal[i]);
// 		auto reslt = list_hash[list_location].check_rpt1(meal[i]);
// 		if (reslt.bool_value)
// 		{
// 			list_hash[list_location].insert_head(meal[i]);
// 			//printf("\n");
// 		}
// 		else if (reslt.chongfu<1)
// 			rept_hash.insert_tail(meal[i]);
// 		else;
// 	}
// 	auto p = rept_hash.head;
// 	while ((p = p->succ) != rept_hash.tail)
// 	{
// 		printf("%s\n", p->meal_name);
// 	}
// }

