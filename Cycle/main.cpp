//没有对二叉堆进行封装，因为没有必要
#define _CRT_SECURE_NO_DEPRECATE
#define maxn 100001
#include<stdio.h>
#include<string.h>
using namespace std;
char str1[maxn];
char str2[maxn];
int find_in2(char*str1,char*str2)
{
	auto mi = 0;
	while (str2[mi++] != str1[0]);
	return --mi;
}
int answer = 0;
int position;
bool compare(int&head2,int l1,int head1,char*str1,char*str2)
{
	position = head2;
	int second_start=0;
	auto temp = head1;
	while (str1[head1++] == str2[head2++]&&head2<l1) {
		if (!second_start&&str2[head2] == str1[temp])second_start = head2 ;
	}
	if (str1[head1 - 1] == str2[head2 - 1]) { answer = 1; 
	return true; }
	else {
		if(second_start)head2 = second_start;
		else while (head2 < l1&&str2[head2] != str1[temp])head2++;
		return false;
	}
}
bool check_rest(int l1,char*str1,char*str2)
{
	int i = 0, j = l1 - position;
	while (i < position&&str2[i++] == str1[j++]);
	return i == position ? true : false;
}
int main()
{
#ifndef _OJ_
	freopen("cycle.txt", "r", stdin);
	// freopen("travelout.txt", "w", stdout);
#endif
	while (scanf("%s %s", &str1, &str2)!=EOF)
	{
		answer=0;
		int l1 = strlen(str1), l2 = strlen(str2);
		if (l1 == l2) {
			int compare_head = find_in2(str1,str2);
			auto temp = compare_head;
			while (!compare(compare_head, l1, 0, str1, str2) && compare_head < l1);
				if (answer&&check_rest(l1,str1,str2))printf("YES\n");
				else printf("NO\n");
		}
		else printf("NO\n");
	}
}
 

// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>
// #define MAXSIZE 100000
// int* bulidNext(char* P,int m){
// 	int *N=(int*)malloc(m*sizeof(int));
// 	int j=0,t=N[0]=-1;
// 	while(j<m-1){
// 		if(t<0||P[j]==P[t]){
// 			j++;t++;
// 			N[j]=(P[j]!=P[t]?t:N[t]);
// 		}
// 		else t=N[t];
// 	}
// 	return N;
// }
// int KMP(char* P,char* T,int n,int m){
// 	int i=0,j=0;
// 	int *next=bulidNext(P,m);
// 	while(i<n&&j<m){
// 		if(j<0||T[i]==P[j]){i++;j++;}
// 		else j=next[j];
// 	}
// 	return i-j;
// }
// int main(){
// 	char T[2*MAXSIZE],P[MAXSIZE];
// 	while(scanf("%s %s",T,P)!=EOF){
// 		int n=strlen(T),m=strlen(P);
// 		if(n!=m)puts("NO");
// 		else{
// 			int i,j=0;
// 			for(i=n;i<2*n;i++)
// 				T[i]=T[j++];
// 			n*=2;
// 			if(KMP(P,T,n,m)<=n-m)puts("YES");
// 			else puts("NO");
// 		}
// 	}
// 	return 0;
// }

