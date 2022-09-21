#include<cstdio>
#define MAXSIZE 1600001
int stack[MAXSIZE],op[2*MAXSIZE];//定义栈和标记操作的数组，注意全局数组元素为0 
int i=1,j,k=0,m,n,t,flag=1,top=-1;//i为1,2,...n,k为数组下标，flag标识序列可行性 
void Judge(){
	if(top!=-1&&stack[top]==t){//若栈非空且栈顶元素为t 
		top--;//出栈 
		k++;
	}
	else flag=0;
}
int main(){
	scanf("%d%d",&n,&m);
	while(n--){
		if(!flag)break;
		scanf("%d",&t);
		if(i<=t){//说明t未入栈，需要入栈 
			for(;top<m-1&&i<=t;i++){//将i到t入栈，注意top从-1开始，故top需小于m-1 
				stack[++top]=i;//入栈 
				op[k++]=1;//1为push，0为pop 
			}
			Judge();
		}
		else Judge();
	}
	if(!flag)//根据可行标识输出 
	puts("No");
	else 
	for(i=0;i<k;i++)
	if(op[i])
	puts("push");
	else
	puts("pop");
	return 0;
}

// #pragma warning(disable:4996)
// #include<stdio.h>
// #include<string.h>
// #define maxn 1600005
// using namespace std;
// char a[2*maxn][5];//记录操作命令
// int stack[maxn];
// char pop[5] = "pop", push[5] = "push";
// int main()
// {
// 	int m = 0, n = 0, compare = 0, cap = 0, length, size = 0;//cap是a中目前元素位置
// #ifndef _OJ_
// 	freopen("trainin.txt", "r", stdin);
// 	freopen("trainout.txt", "w", stdout);
// #endif
// 	scanf("%d %d", &n, &m);//n是数目，m是栈的容量
// 	length = n;
// 	int num, e;
// 	while (n--&&size < m && compare < length)
// 	{
// 		scanf("%d", &num);
// 		//栈为空的时候，则先push，再pop出来进行比较
// 		if (size == 0) {
// 			stack[size++] = ++compare;
// 			memcpy(a[cap++], push, strlen(push));
// 		}
// 		//将栈的内容pop出来进行比较
// 		e = stack[--size];
// 		//如果栈的内容与目标num相等，则不再push进去
// 		if (e == num)memcpy(a[cap++], pop, strlen(pop));
// 		//先将内容push进去，比较push进去的内容是否大于num，当大于，则结束
// 		//否则，则继续往栈添加元素
// 		//添加完元素之后就pop出来进行比较，若相等，则结束；否则，继续添加，直至，添加了最后一个元素,若仍然不相等，则结束
// 		else
// 		{
// 			stack[size++] = e;
// 			if (e > num) { printf("No\n"); return 0; }
// 			while (compare < length&&size < m)
// 			{
// 				memcpy(a[cap++], push, strlen(push));
// 				stack[size++] = ++compare;
// 				if ((e = stack[--size]) == num)
// 				{
// 					memcpy(a[cap++], pop, strlen(pop));
// 					break;
// 				}
// 				else if(compare==length){ printf("No\n"); return 0; }
// 				stack[size++] = e;
// 			}
// 		}
// 	}
// 	n++;
// 	if (compare <= length && size < m)
// 	{
// 		while (n--)
// 		{
// 			scanf("%d", &num);
// 			if (stack[--size] == num) { memcpy(a[cap++], pop, strlen(pop)); }
// 			else { printf("No\n"); return 0; }
// 		}
// 	}
// 	else if (size >= m) { printf("No\n"); return 0; }
// 	for (auto i = 0; i < cap; i++)printf("%s\n",a[i]);
// }

// #pragma warning(disable:4996)
// #include<stdio.h>
// #include<string.h>
// #define maxn 1600005
// using namespace std;
// char a[2*maxn][5];//记录操作命令
// int stack[maxn],b[maxn];
// char pop[5] = "pop", push[5] = "push";
// int size=0,compare = 0;
// int po_p()
// {
// 	return stack[--size];
// }
// void pus_h()
// {
// 	stack[size++] = ++compare;
// }
// int main()
// {
// 	int m = 0, n = 0,cap = 0, length,i=0;//cap是a中目前元素位置
// #ifndef _OJ_
// 	freopen("trainin.txt", "r", stdin);
// 	freopen("trainout.txt", "w", stdout);
// #endif
// 	scanf("%d %d", &n, &m);//n是数目，m是栈的容量
// 	length = n;
// 	int num;
// 	while(i<n){scanf("%d", &b[i++]);}
// 	i=0;
// 	while (size <= m &&i<n&&compare<length)
// 	{
// 		if(compare < b[i])
// 		{
// 		pus_h();
// 		memcpy(a[cap++], push, strlen(push));
// 		}
// 		else {
// 			if(po_p()==b[i++])memcpy(a[cap++], pop, strlen(pop));
// 			else{ printf("No\n"); return 0; }
// 		}
// 	}
// 	// for (auto i = 0; i < cap; i++)printf("%s\n",a[i]);
// 	if (compare == length && size <= m)
// 	{
// 		while (i<n)
// 		{
// 			if (po_p() == b[i++]) { memcpy(a[cap++], pop, strlen(pop)); }
// 			else { printf("No\n"); return 0; }
// 		}
// 	}
// 	else if (size > m) { printf("No\n"); return 0; }
// 	for (auto i = 0; i < cap; i++)printf("%s\n",a[i]);
// }



