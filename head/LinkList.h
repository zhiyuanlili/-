#pragma once
#include<stdio.h>
#include<stdlib.h>
#define ERROR 0
#define OK 1
typedef int ElemType_T;
typedef int Status;

typedef struct Node {
	ElemType_T data;
	struct Node *next;
}Node, *LinkList;


//初始化
Status ListInit(LinkList *L) {
	*L = (LinkList)malloc(sizeof(Node));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	return OK;
}


//表长
int ListLength(LinkList L) {
	LinkList p = L;
	int len = 0;
	while (p->next) {
		len++;
		p = p->next;
	}
	return len;
}


//获取元素,用e保存
Status GetElem(LinkList L, int i, ElemType_T *e) {
	int j;
	LinkList p;
	p = L->next;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		j++;
	}
	if (i == j) {
		*e = p->data;
		return OK;
	}
	else
		return ERROR;
}


//插入
Status ListInsert(LinkList*L, int i, ElemType_T e) {
	int j;
	LinkList p, s;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (j == i) {
		s = (LinkList)malloc(sizeof(Node));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return OK;
	}
}


//删除
Status ListDelete(LinkList*L, int i, ElemType_T *e) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	*e = q->data;
	free(q);
	return OK;

}

Status ListDelete_L(LinkList*L, int i) {
	int j;
	LinkList p, q;
	p = *L;
	j = 1;
	while (p->next&&j < i) {
		p = p->next;
		++j;
	}
	if (!(p->next) || j>i)
		return ERROR;
	q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}

//头插
void CreateList_Head(LinkList *L, int n) {
	LinkList p;
	int i;
	*L = (LinkList)malloc(sizeof(Node));
	(*L)->next = NULL;
	printf("输入结点数据:");
	for (i = 0;i < n;i++) {
		p = (LinkList)malloc(sizeof(Node));
		scanf("%d", &(p->data));
		p->next = (*L)->next;
		(*L)->next = p;
	}
}


//尾插
void CreateList_Tail(LinkList*L, int n) {
	LinkList p, r;
	int i;
	*L = (LinkList)malloc(sizeof(Node));
	r = *L;
	printf("输入结点数据:");
	for (i = 0;i < n;i++) {
		p = (Node*)malloc(sizeof(Node));
		scanf("%d", &(p->data));
		r->next = p;
		r = p;
	}
	r->next = NULL;
}


//按位置查找，返回节点
Status ListFind(LinkList L, int i) {
	LinkList p = L->next;
	int j = 1;
	while (p&&j < i) {
		p = p->next;
		j++;
	}
	if (p&&j == i)
		return j;
	else
		return ERROR;
}


//按元素值查找
Status ListFind_elem(LinkList L, ElemType_T x) {
	LinkList p = L->next;
	while (p) {
		if (p->data == x)
			return OK;
		else
			p = p->next;
	}
	return ERROR;
}


//整表删除
Status ClearList(LinkList *L) {
	LinkList p, q;
	p = (*L)->next;
	while (p) {
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;
	return OK;
}

void swap(int &a, int &b)
{
	int temp;
	temp = a;
	a = b;
	b = temp;
}

//双指针都从头开始
LinkList partation(LinkList low, LinkList high) {
	int key = low->data;
	LinkList p = low;
	LinkList q = low->next;

	while (q != high) {
		if (q->data < key) {
			p = p->next;
			swap(p->data, q->data);
		}
		q = q->next;
	}
	swap(p->data, low->data);
	return p;
}

void Qsort(LinkList low, LinkList high) {
	if (low != high) {
		LinkList pivot = partation(low, high);
		Qsort(low, pivot);
		Qsort(pivot->next, high);
	}
}

void sort(LinkList L) {
	Qsort(L->next, NULL);
}

LinkList remove(LinkList L) {
	//去重
	LinkList p = L->next;
	int count = 1;
	while (p->next) {
		if (p->data == p->next->data) {
			ListDelete_L(&L, count + 1);
		}
		else {
			count++;
			p = p->next;
		}
	}
	return L;
}

//交集，双指针
LinkList intersection(LinkList L1, LinkList L2) {
	LinkList p = L1->next, head, q, t;
	//ListInit(&head);
	ListInit(&q);
	head = q;
	int i = 1;
	while (p) {
		if (ListFind_elem(L2, p->data)) {
			ListInsert(&q, i, p->data);
			i++;
		}
		p = p->next;
	}
	return head;
}

//并集，合并去重
LinkList Union(LinkList L1, LinkList L2) {
	LinkList L, p = L1->next, q = L2->next;
	int count = 1;
	ListInit(&L);
	while (p) {
		ListInsert(&L, count, p->data);
		count++;
		p = p->next;
	}
	while (q) {
		ListInsert(&L, count, q->data);
		count++;
		q = q->next;
	}
	sort(L);
	remove(L);
	return L;

}

void Print(LinkList L) {
	LinkList p = L->next;
	while (p) {
		printf("%-5d", p->data);
		p = p->next;
	}
}

void Menue() {
	//显示菜单
	printf("线性表子系统\n");
	printf("==============================================\n");
	printf("||                 1--建立                  ||\n");
	printf("||                 2--插入                  ||\n");
	printf("||                 3--删除                  ||\n");
	printf("||                 4--按位置查找            ||\n");
	printf("||                 5--按值查找              ||\n");
	printf("||                 6--求表长                ||\n");
	printf("||                 7--求交集                ||\n");
	printf("||                 8--求并集                ||\n");
	printf("||                 0--返回                  ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-6):");
}

void linklist() {
	LinkList L,L1,L2,p;
	ElemType_T e;
	int length,length2, i,j;
	char c1, c2, a;
	c1 = 'y';
	while (c1 == 'y' || c1 == 'Y') {
		Menue();
		scanf("%c", &c2);
		getchar();
		switch (c2) {
		case '1':
			ListInit(&L);
			printf("请输入要建立线性表的长度:");
			scanf("%d", &length);
			CreateList_Tail(&L, length);
			printf("建立后的线性表为:\n");
			Print(L);
			getchar();
			break;
		case '2':
			printf("请输入要插入的元素位置:");
			scanf("%d", &i);
			printf("请输入要插入的元素值:");
			scanf("%d", &e);
			ListInsert(&L, i, e);
			printf("插入元素%d后的线性表为:\n", e);
			Print(L);
			getchar();
			break;
		case '3':
			printf("请输入要删除元素的位置:");
			scanf("%d", &i);
			ListDelete(&L, i, &e);
			printf("删除第%d位后的元素后的线性表为:\n", i);
			Print(L);
			getchar();
			break;
		case '4':
			printf("请输入查找的元素位置(大于等于1的整数):");
			scanf("%d", &i);
			if (ListFind(L, i))
				printf("查找成功");
			else
				printf("查找失败");
			getchar();
			break;
		case '5':
			printf("请输入要查找的元素:");
			scanf("%d", &e);
			if (ListFind_elem(L, e))
				printf("查找成功");
			else
				printf("查找失败");
			getchar();
			break;
		case '6':
			printf("线性表的长度为:%d\n", ListLength(L));
			break;
		case '7':
			ListInit(&L1);
			printf("请输入要建立第二个线性表的长度:");
			scanf("%d", &length2);
			CreateList_Tail(&L1, length2);
			printf("建立后的第二个线性表为:\n");
			Print(L1);
			p = intersection(L, L1);
			printf("\n交集为:");
			Print(p);
			getchar();
			break;
		case '8':
			ListInit(&L2);
			printf("请输入要建立第二个线性表的长度:");
			scanf("%d", &length2);
			CreateList_Tail(&L2, length2);
			printf("建立后的第二个线性表为:\n");
			Print(L2);
			p = Union(L, L2);
			printf("\n并集为:");
			Print(p);
			break;
		case '0':
			c1 = 'n';
			break;
		default:
			printf("输入错误，请输入0-9进行选择\n");
			break;
		}
		if (c2 != '0') {
			printf("\n按回车键继续，按任意键返回主菜单\n");
			a = getchar();
			if (a != '\n') {
				getchar();
				c1 = 'n';
			}
		}
	}
}