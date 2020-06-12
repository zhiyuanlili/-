#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define OK 1
#define ERROR 0
#define MAX 200
typedef int Status;

typedef struct String {
	char data[MAX + 1];
	int n;
}String;

//初始化建立新串
Status InitString(String *S) {
	int i = 0,n=0;
	while ((S->data[i] = getchar()) != '\n') {
		i++;
		n++;
	}
	S->n = n;
	return OK;
}

//打印
void Print_S(String S) {
	for (int i = 0;i < S.n;i++)
		printf("%c",S.data[i]);
	printf("\n");
}

//求串长
int GetSlength(String S) {
	return S.n;
}

//求子串
Status SubStr(String S, String *T,int pos, int len) {
	if (pos<1 || pos>S.n || len<0 || pos + len - 1>S.n)
		return ERROR;
	int i;
	for (i = 0;i <= len;i++) {
		T->data[i] = S.data[i + pos - 1];
	}
	T->n = len;
	return OK;
}

//插入
Status StrInsert(String *S1, String S2, int pos) {
	if (pos<1 || pos>S1->n)
		return ERROR;
	int j;
	for (j = S1->n - 1;j >= pos - 1;j--)
		S1->data[j + S2.n] = S1->data[j];
		
	for (j = 0;j < S2.n;j++)
		S1->data[pos + j - 1] = S2.data[j];
	S1->n = S1->n + S2.n;
	return OK;
}

//删除子串
Status DeleteStr(String *S, int pos, int len) {
	if (pos<1 || pos>S->n || len + pos - 1>S->n)
		return ERROR;
	for (int i = pos + len;i <= S->n;i++)
		S->data[i - len] = S->data[i];
	S->n -= len;
	return OK;
}

//串比较
int Strcmp(String S1, String S2) {
	int i;
	for (i = 0;i < S1.n&&i < S2.n;i++) {
		if (S1.data[i] > S2.data[i])
			return 1;
		else if (S1.data[i] < S2.data[i])
			return -1;
	}
	if (i < S1.n)
		return 1;
	if (i < S2.n)
		return -1;
	return 0;
}

//串连接
Status Concat(String *S1, String S2) {
	if (S1->n == MAX || S1->n + S2.n >= MAX)
		return ERROR;
	int i,j,length=S1->n+S2.n;
	for (i = S1->n,j=0;i < length;i++,j++) {
		S1->data[i] = S2.data[j];
	}
	S1->n = length;
	return OK;
}

void getNext(String p, int * next){
	next[0] = -1;
	int i = 0, j = -1;
	while (i < p.n){
		if (j == -1 || p.data[i] == p.data[j]){
			++i;
			++j;
			next[i] = j;
		}
		else
			j = next[j];
	}
}
//KMP查找子串
int KMP(String S, String T) {
	int i = 0;
	int j = 0;
	int next[255];
	getNext(T, next);
	while (i < S.n && j < T.n) {
		if (j == -1 || S.data[i] == T.data[j]) {
			i++;
			j++;
		}
		else {
			j = next[j];
		}
	}
	if (j == T.n)
		return i - j;
	else
		return -1;
}

//子串替换
Status StrRep(String *S, String T, String R) {
	int pos;
	if ((pos = KMP(*S, T)) == -1 || T.n != R.n) {
		printf("要被替换的串不在S中");
		return ERROR;

	}
	int i;
	while (pos != -1) {
		for (i = 0;i < T.n;pos++, i++)
			S->data[pos] = R.data[i];
		pos = KMP(*S, T);
	}
	return OK;
}


void Menue3() {
	printf("串子系统\n");
	printf("==============================================\n");
	printf("||               1--建立新串                ||\n");
	printf("||               2--求子串                  ||\n");
	printf("||               3--插入子串                ||\n");
	printf("||               4--删除子串                ||\n");
	printf("||               5--查找子串                ||\n");
	printf("||               6--比较两串                ||\n");
	printf("||               7--连接两串                ||\n");
	printf("||               8--子串替换                ||\n");
	printf("||               9--显示                    ||\n");
	printf("||               10--求串长                 ||\n");
	printf("||               0--返回                    ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-10):");
}

void string() {
	String S, T, R;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue3();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("请输入串S的内容:");
			InitString(&S);
			printf("新建成功");
			break;
		case '2':
			printf("请输入S的子串的起始位置和子串长度:");
			scanf("%d%d",&i,&n);
			SubStr(S, &T, i, n);
			printf("子串为:");
			Print_S(T);
			getchar();
			break;
		case '3':
			printf("请输入插入到串S位置:");
			scanf("%d",&i);
			getchar();
			printf("请输入要插入的子串:");
			InitString(&T);
			StrInsert(&S, T, i);
			printf("插入后的子串为:");
			Print_S(S);
			break;
		case '4':
			printf("请输入要删除S的子串起始位置和长度:");
			scanf("%d%d",&i,&n);
			DeleteStr(&S, i-1, n);
			printf("删除后为:");
			Print_S(S);
			getchar();
			break;
		case '5':
			printf("请输入要在S中查找的子串:");
			InitString(&T);
			i = KMP(S, T);
			if (i == -1)
				printf("该子串不在串S中");
			else
				printf("该子串在串S的第%d位到%d位",i+1,i+T.n);
			break;
		case '6':
			printf("请输入要与S比较的串T:");
			InitString(&T);
			i = Strcmp(S, T);
			if (i == 1)
				printf("S大");
			else if (i == 0)
				printf("两串相等");
			else
				printf("T大");
			break;
		case '7':
			printf("请输入要连接到S的串T:");
			InitString(&T);
			Concat(&S, T);
			printf("连接后的S为:");
			Print_S(S);
			break;
		case '8':
			printf("请输入要在S中要被替换的部分:");
			InitString(&T);
			printf("请输入要替换的串:");
			InitString(&R);
			if (StrRep(&S, T, R)) {
				printf("替换后S为:");
				Print_S(S);
			}
			break;
		case '9':
			printf("串为:");
			Print_S(S);
			break;
		case '10':
			printf("串长为:%d", GetSlength(S));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("出入错误,请输入0-10进行选择!");
			break;

		}
		if (ch2 != '0') {
			printf("\n按回车键继续，按任意键返回主菜单!\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				ch1 = 'n';
			}
		}
	}
}