#pragma once
#include<stdio.h>
#include<stdlib.h>
#define MAXVEX 100
typedef char VertexType;
typedef int EdgeType;
bool visited[MAXVEX];

typedef struct EdgeNode {//边表
	int adjvex;//邻接点域，储存该点对应的下标
	struct EdgeNode *next;//链域，指向下一个邻接点
}EdgeNode;

typedef struct VertexNode {//顶点表
	VertexType data;//数据域
	EdgeNode*firstedge;//边表头指针
}VertexNode, AdjList[MAXVEX];

typedef struct {
	AdjList adjList;
	int numVertexes, numEdges;//图中的顶点数和边数
}GraphAdjList;

//借用队列完成BFS
#define MAXSIZE 100
#define OK 1
#define ERROR 0
typedef int ElemTypeG;
typedef int Status;
typedef struct {
	ElemTypeG data[MAXSIZE];
	int front;
	int rear;
}SqQueue;

//初始化
Status InitQueue_G(SqQueue *Q) {
	Q->front = 0;
	Q->rear = 0;
	return OK;
}

//入队--尾部
Status EnQueue_G(SqQueue *Q, ElemTypeG e) {
	if ((Q->rear + 1) % MAXSIZE == Q->front)//队满（要有一个空缺）
		return ERROR;
	Q->data[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;//rear指针向后移一个位置，若到了最后则转到队头
}

//出队--头部
Status DeQueue_G(SqQueue*Q, ElemTypeG*e) {
	if (Q->front == Q->rear)//队空
		return ERROR;
	*e = Q->data[Q->front];
	Q->front = (Q->front + 1) % MAXSIZE;
	return OK;
}

void CreatALGraph(GraphAdjList *G, int n) {
	if (n == 1)
		printf("=========将建立一个有向图=========\n");
	else
		printf("=========将建立一个无向图=========\n");
	int i, j, k;
	EdgeNode *e;
	printf("输入顶点数和边数:");
	scanf("%d%d", &G->numVertexes, &G->numEdges);
	for (i = 0;i < G->numVertexes;i++) {
		//建立顶点表
		printf("输入第%d个点:", i);
		scanf("\n%c", &(G->adjList[i].data));
		G->adjList[i].firstedge = NULL;//先将边表置为空表
	}

	for (k = 0;k < G->numEdges;k++) {
		//建立边表
		printf("输入第%d条边(Vi,Vj)上的顶点序号:", k);
		scanf("\n%d,%d", &i, &j);
		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = j;//邻接序号为j
		e->next = G->adjList[i].firstedge;//采用头插法插入
		G->adjList[i].firstedge = e;

		e = (EdgeNode*)malloc(sizeof(EdgeNode));
		e->adjvex = i;
		e->next = G->adjList[j].firstedge;
		G->adjList[j].firstedge = e;
	}
}
void DFS(GraphAdjList GL, int i) {
	EdgeNode *p;
	visited[i] = true;
	printf("%c ", GL.adjList[i].data);
	p = GL.adjList[i].firstedge;
	while (p) {
		if (!visited[p->adjvex])
			DFS(GL, p->adjvex);//对为访问的邻接顶点递归调用
		p = p->next;
	}
}

void DFSTraverse(GraphAdjList GL) {
	int i;
	for (i = 0;i < GL.numVertexes;i++)
		visited[i] = false;
	for (i = 0;i < GL.numVertexes;i++)
		if (!visited[i])
			DFS(GL, i);
}

void Print_G(GraphAdjList G) {
	int i;
	EdgeNode *e;
	for (i = 0;i < G.numVertexes;i++) {
		printf("%c", G.adjList[i].data);
		e = G.adjList[i].firstedge;
		while (e) {
			printf("-->%d", e->adjvex);
			e = e->next;
		}
		printf("\n");
	}
}

void BFSTraverse(GraphAdjList GL) {
	int i;
	EdgeNode *p;
	SqQueue Q;
	for (i = 0;i < GL.numVertexes;i++)
		visited[i] = false;
	InitQueue_G(&Q);
	for (i = 0;i < GL.numVertexes;i++) {
		if (!visited[i]) {
			visited[i] = true;
			printf("%c ", GL.adjList[i].data);
			EnQueue_G(&Q, i);
			while (Q.front != Q.rear) {
				DeQueue_G(&Q, &i);
				p = GL.adjList[i].firstedge;
				while (p) {
					if (!visited[p->adjvex]) {
						visited[p->adjvex] = true;
						printf("%c ", GL.adjList[p->adjvex].data);
						EnQueue_G(&Q, p->adjvex);
					}
					p = p->next;
				}
			}
		}
	}

}

void Menue5() {
	printf("图子系统\n");
	printf("==============================================\n");
	printf("||                 1--更新邻接表            ||\n");
	printf("||                 2--深度优先遍历          ||\n");
	printf("||                 3--广度优先遍历          ||\n");
	printf("||                 4--显示邻接图            ||\n");
	printf("||                 0--返回                  ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-4):");
}

void graph() {
	GraphAdjList G;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue5();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("要建立的是有向图(1)还是无向图(0),请选择(输入1或者0):");
			scanf("%d",&n);
			CreatALGraph(&G,n);
			getchar();
			break;
		case '2':
			printf("深度优先遍历的序列为:");
			DFSTraverse(G);
			break;
		case '3':
			printf("广度优先遍历的序列为:");
			BFSTraverse(G);
			break;
		case '4':
			printf("图为:\n");
			Print_G(G);
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