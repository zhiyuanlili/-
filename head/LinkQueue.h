#pragma once
#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define ERROR 0
typedef int QElemType;
typedef int Status;
typedef struct QNode {
	QElemType data;
	struct QNode *next;
}QNode,*QueuePtr;

typedef struct {
	QueuePtr front, rear;
}LinkQueue;

Status InitLinkQuue(LinkQueue*Q) {
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}

//入队
Status EnQueue(LinkQueue*Q, QElemType e) {
	QueuePtr s = (QueuePtr)malloc(sizeof(QNode));
	if (!s)
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}

//出队
Status DeQueue(LinkQueue*Q, QElemType*e) {
	QueuePtr p;
	if (Q->front == Q->rear)
		return ERROR;
	p = Q->front->next;
	*e = p->data;
	Q->front->next = p->next;
	if (Q->rear == p)//如果队头是队尾
		Q->rear = Q->front;
	free(p);
	return OK;
}
//判断队空
Status EmptyQueue(LinkQueue *Q) {
	if (Q->front == Q->rear)//空
		return OK;
	return ERROR;
}

//取头
Status GetQueue(LinkQueue*Q, QElemType*e) {
	if (EmptyQueue(Q))
		return ERROR;
	*e = Q->front->next->data;
}


//显示
void Print_Q(LinkQueue*Q) {
	QNode *p=Q->front->next;
	while (p) {
		printf("%-5d",p->data);
		p = p->next;
	}
	printf("\n");
}

void Menue2() {
	//菜单
	printf("队列子系统\n");
	printf("==============================================\n");
	printf("||               1--初始化队列              ||\n");
	printf("||               2--入队                    ||\n");
	printf("||               3--出队                    ||\n");
	printf("||               4--求队头元素              ||\n");
	printf("||               5--显示队中元素            ||\n");
	printf("||               0--返回                    ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-5):");
}

void linkqueue() {
	int i, n;
	QElemType x;
	LinkQueue Q;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue2();
		scanf("%c",&ch2);
		getchar();
		switch (ch2) {
		case '1':
			InitLinkQuue(&Q);
			printf("初始化队列完成");
			break;
		case '2':
			printf("请输入要入队的元素个数:");
			scanf("%d",&n);
			printf("请输入%d个元素:",n);
			for (i = 0;i < n;i++) {
				scanf("%d",&x);
				EnQueue(&Q, x);
			}
			printf("入队后队列为:");
			Print_Q(&Q);
			getchar();
			break;
		case '3':
			printf("请输入要出队的元素个数:");
			scanf("%d",&n);
			printf("出队的元素顺序依次为:");
			for (i = 0;i < n;i++) {
				DeQueue(&Q, &x);
				printf("%-5d",x);
			}
			getchar();
			break;
		case '4':
			GetQueue(&Q, &x);
			printf("当前队头元素为:%d",x);
			break;
		case '5':
			printf("当前队中元素为:");
			Print_Q(&Q);
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("出入错误,请输入0-5进行选择!");
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