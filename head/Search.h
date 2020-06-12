#pragma once
#include<stdio.h>
#include<stdlib.h>
#define FALSE 0
#define TRUE 1
#define MAXSIZE 100
typedef int Status;
typedef struct {
	int key;
}SearchL;

//顺序查找
int Search(SearchL *a, int n, int key) {
	int i;
	a[0].key = key;
	i = n;
	while (a[i].key != key)
		i--;
	return i;
}

//二分查找
int Binary_Search(SearchL *a, int n, int key) {
	//非递归
	int high, low,mid;
	low = 0;
	high = n;
	while (low <= high) {
		mid = (low + high) / 2;
		if (key < a[mid].key)
			high = mid - 1;
		else if (key>a[mid].key)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

typedef int KeyType;
typedef struct {
	KeyType key;
	int low;
	int high;
}IdxType;

int blocksearch(int key, SearchL a[], IdxType index_key[],int m,int n) {
	int i = 0, j = 1;
	int k = m / n;
	while (i < k) {
		index_key[i].low = j;
		index_key[i].high = j + n - 1;
		index_key[i].key = a[j + n - 1].key;
		j += n;
		i++;
	}
	if (m%n != 0) {
		index_key[i].low = j;
		index_key[i].high = m - 1;
		index_key[i].key = a[m - 1].key;
		i++;
	}
	k = i;

	for (i = 0;i<k && key>index_key[i].key;i++);
	if (i >= k) return 0;
	j = index_key[i].low;
	for (;j < index_key[i].high&&key != a[j].key;j++);
	if (j > index_key[i].high) return 0;
	return j;
}

typedef struct BiTNode_S {
	int data;
	struct BiTNode_S*lchild, *rchild;
}BiTNode_S, *BiTree_S;

/*
指针f指向T的双亲，其初始调用值为NULL
如果查找成功，则指针P指向该数据元素节点，并返回TRUE
否则指针p指向查找路径上访问的最后一个节点并返回FALSE
*/
Status SearchBST(BiTree_S T, int key, BiTree_S f, BiTree_S *p) {
	if (!T) {
		*p = f;
		return FALSE;
	}
	else if (key == T->data) {
		*p = T;
		return TRUE;
	}
	else if (key < T->data)
		return SearchBST(T->lchild, key, T, p);
	else
		return SearchBST(T->rchild, key, T, p);
}

//插入
Status InsertBST(BiTree_S*T, int key) {
	BiTree_S p, s;
	if (!SearchBST(*T, key, NULL, &p)) {
		s = (BiTree_S)malloc(sizeof(BiTNode_S));//查找不成功则插入
		s->data = key;
		s->lchild = s->rchild = NULL;
		if (!p)
			*T = s;//插入s为新的根节点
		else if (key < p->data)
			p->lchild = s;
		else
			p->rchild = s;
		return TRUE;
	}
	else
		return FALSE;
}

//建立
void BuildBST(BiTree_S *T, int *data,int n) {
	int i;
	for (i = 1;i <= n;i++)
		InsertBST(T, data[i]);
}

//删除
Status Delete(BiTree_S *p) {
	BiTree_S q, s;
	if ((*p)->rchild == NULL) {	//右子树空则只需要重接它的左子树
		q = *p;
		*p = (*p)->lchild;
		free(q);
	}
	else if ((*p)->lchild == NULL) {//左子树空则只需要重接它的右子树
		q = *p;
		*p = (*p)->rchild;
		free(q);
	}
	else {//左右子树均不空的情况
		  /*
		  方法：
		  取右子树中的最小元素替代   或者   取左子树中的最大元素替代
		  */
		  //此处选取左子树的最大元素替代
		q = *p;
		s = (*p)->lchild;
		while (s->rchild) {//转左，然后向右到尽头
			q = s;
			s = s->rchild;
		}
		(*p)->data = s->data;//s指向被删节点的直接前驱
		if (q != *p)
			q->rchild = s->lchild;//重接q的右子树
		else//不可能同时存在左右子树，如果同时存在则需要再向下
			q->lchild = s->lchild;
		free(s);
	}
	return TRUE;
}

Status DeleteBST(BiTree_S *T, int key) {
	if (!*T)
		return FALSE;
	else {
		if (key == (*T)->data)
			return Delete(T);
		else if (key < (*T)->data)
			return DeleteBST(&(*T)->lchild, key);
		else
			return DeleteBST(&(*T)->rchild, key);
	}
}

//用广义表表示二叉树
void Print_BTree(BiTree_S T) {
	printf("%d", T->data);
	if (T->lchild != NULL) {
		printf("(");
		Print_BTree(T->lchild);
		if (T->rchild == NULL)
			printf(",)");
	}
	if (T->rchild != NULL) {
		if (T->lchild == NULL)
			printf("(");
		printf(",");
		Print_BTree(T->rchild);
		printf(")");
	}
}

void MenueBTree() {
	printf("二叉排序树\n");
	printf("==============================================\n");
	printf("||             1--建立二叉排序树            ||\n");
	printf("||             2--插入一个元素              ||\n");
	printf("||             3--删除一个元素              ||\n");
	printf("||             4--查找一个元素              ||\n");
	printf("||             5--广义表表示法显示          ||\n");
	printf("||             0--返回                      ||\n");
	printf("==============================================\n");
	printf("请输入序号(0-4)选择要进行的操作:");
}

void BTfunction() {
	KeyType s[MAXSIZE];
	BiTree_S T = NULL;
	BiTree_S p;
	int i, n, x;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		MenueBTree();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("请输入要生成二叉排序树的关键字的个数:");
			scanf("%d",&n);
			printf("请输入二叉排序树的各个关键字:");
			for (i = 1;i <= n;i++) {
				scanf("%d",&s[i]);
			}
			BuildBST(&T, s, n);
			printf("二叉排序树建立成功,广义表表示法为:(");
			Print_BTree(T);
			printf(")");
			getchar();
			break;
		case '2':
			printf("请输入要插入的元素值:");
			scanf("%d",&x);
			InsertBST(&T, x);
			printf("插入后的二叉排序树为:");
			Print_BTree(T);
			getchar();
			break;
		case '3':
			printf("请输入要删除的元素:");
			scanf("%d",&x);
			DeleteBST(&T, x);
			printf("删除后的二叉排序树为:");
			Print_BTree(T);
			getchar();
			break;
		case '4':
			printf("请输入要查找的元素值:");
			scanf("%d",&x);
			if(SearchBST(T, x, NULL, &p))
				printf("在二叉排序树中存在元素%d",x);
			else
				printf("在二叉排序树中不存在元素%d", x);
			getchar();
			break;
		case '5':
			printf("二叉排序树为:(");
			Print_BTree(T);
			printf(")");
			break;
		case '0':
			return;
			break;
		default:
			printf("输入错误,请输入0-5进行选择!");
			break;
		}
		if (ch2 != '0') {
			printf("\n按回车键继续，按任意键返回查找子系统!\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				ch1 = 'n';
			}
		}
	}
}

void Menue6() {
	printf("查找子系统\n");
	printf("==============================================\n");
	printf("||                 1--顺序查找              ||\n");
	printf("||                 2--折半查找              ||\n");
	printf("||                 3--分块查找              ||\n");
	printf("||                 4--二叉排序树查找        ||\n");
	printf("||                 0--返回                  ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-4):");
}

void search() {
	SearchL L[MAXSIZE];
	IdxType idx[MAXSIZE];
	int i, n,x,index,m;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue6();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("请输入元素个数(0-%d):",MAXSIZE-1);
			scanf("%d",&n);
			printf("请输入%d个表中的关键字(整数):",n);
			for (i = 1;i <= n;i++)
				scanf("%d",&L[i].key);
			printf("请输入要查找的关键字:");
			scanf("%d",&x);
			if ((index = Search(L, n, x)) != 0)
				printf("该元素在表中的位置为:%d", index);
			else
				printf("该元素不在表中");
			getchar();
			break;
		case '2':
			printf("请输入表的元素个数(0-%d):", MAXSIZE - 1);
			scanf("%d", &n);
			printf("请按照从小到大的顺序输入%d个关键字(为整数):", n);
			for (i = 1;i <= n;i++)
				scanf("%d", &L[i].key);
			printf("请输入要查找的关键字:");
			scanf("%d", &x);
			if((index=Binary_Search(L,n,x))!=0)
				printf("该元素在表中的位置为:%d", index);
			else
				printf("该元素不在表中");
			getchar();
			break;
		case '3':
			printf("请输入表的元素个数(0-%d):", MAXSIZE - 1);
			scanf("%d", &m);
			printf("请输入表中的关键字(为整数)，要求块内无序，块间有序:\n");
			for (i = 1;i <= m;i++)
				scanf("%d", &L[i].key);
			printf("表输入索引表每块的大小:");
			scanf("%d", &n);
			printf("请输入要查找的关键字:");
			scanf("%d", &x);
			if((index=blocksearch(x, L, idx, m, n))!=0)
				printf("该元素在表中的位置为:%d", index);
			else
				printf("该元素不在表中");
			getchar();
			break;
		case '4':
			BTfunction();
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("出入错误,请输入0-4进行选择!");
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