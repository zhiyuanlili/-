#pragma once
#include<stdio.h>
#include<stdlib.h>

typedef char TElemType;
//二叉树的二叉链表结点结构
typedef struct BiTNode {
	TElemType data;
	struct BiTNode *lchild, *rchild;
}BiTNode, *BiTree;

//借用队列来完成层序遍历
typedef char QType;
typedef int Status;
typedef struct QN {
	BiTree data;//队列元素为树结点
	struct QN *next;
}QN, *QPtr;

typedef struct {
	QPtr front, rear;
}LinkQueue_T;

//初始化一个队列
Status InitLinkQuue_T(LinkQueue_T*Q) {
	Q->front = Q->rear = (QPtr)malloc(sizeof(QN));
	if (!Q->front)
		return ERROR;
	Q->front->next = NULL;
	return OK;
}

//入队
Status EnQueue_T(LinkQueue_T*Q, BiTree e) {
	QPtr s = (QPtr)malloc(sizeof(QN));
	if (!s)
		return ERROR;
	s->data = e;
	s->next = NULL;
	Q->rear->next = s;
	Q->rear = s;
	return OK;
}

//出队
Status DeQueue_T(LinkQueue_T*Q, BiTree*e) {
	QPtr p;
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


void CreateTree(BiTree *T) {
	/*
		A
	B		C
	构建此二叉树输入AB##C##
	*/
	TElemType c;
	scanf("%c",&c);
	if (c == '#')//输入结束标识符
		*T = NULL;
	else {
		(*T) = (BiTree)malloc(sizeof(BiTNode));
		if (!*T)
			exit(0);
		(*T)->data = c;
		CreateTree(&(*T)->lchild);//构造左子树
		CreateTree(&(*T)->rchild);//构造右子树
	}
}

void PreOrderTraverse(BiTree T) {
	//前序遍历
	if (!T)
		return;
	printf("%c",T->data);
	PreOrderTraverse(T->lchild);//遍历左子树
	PreOrderTraverse(T->rchild);//遍历右子树
}

void InOrderTraverse(BiTree T) {
	//中序遍历
	if (!T)
		return;
	InOrderTraverse(T->lchild);
	printf("%c",T->data);
	InOrderTraverse(T->rchild);
}

void PostOrderTraverse(BiTree T) {
	//后序遍历
	if (!T)
		return;
	PostOrderTraverse(T->lchild);
	PostOrderTraverse(T->rchild);
	printf("%c",T->data);
}

void LevelTraverse(BiTree T) {
	BiTree X = T;
	LinkQueue_T Q;
	InitLinkQuue_T(&Q);
	EnQueue_T(&Q, X);//入队
	while (Q.front!=Q.rear) {
		DeQueue_T(&Q, &X);
		printf("%c",X->data);
		if (X->lchild)
			EnQueue_T(&Q, X->lchild);
		if (X->rchild)
			EnQueue_T(&Q, X->rchild);
	} 
}

//求树的节点数
int TreeNodeNum(BiTree T) {
	if (!T)
		return 0;
	return 1 + TreeNodeNum(T->lchild) + TreeNodeNum(T->rchild);
}

//求树的叶子结点
int TreeLeafNum(BiTree T) {
	if (!T)
		return 0;
	if (T->lchild == NULL&&T->rchild == NULL)
		return 1;
	return TreeLeafNum(T->lchild) + TreeLeafNum(T->rchild);
}

//求树的深度
int TreeDepth(BiTree T) {
	if (!T)
		return 0;
	return TreeDepth(T->lchild) > TreeDepth(T->rchild) ? TreeDepth(T->lchild) + 1 : TreeDepth(T->rchild) + 1;
}

//用广义表表示二叉树
void Print_Tree(BiTree T) {
	printf("%c",T->data);
	if (T->lchild != NULL) {
		printf("(");
		Print_Tree(T->lchild);
		if (T->rchild == NULL)
			printf(",)");
	}
	if (T->rchild != NULL) {
		if (T->lchild == NULL) 
			printf("(");
		printf(",");
		Print_Tree(T->rchild);
		printf(")");
	}
}

void Menue4() {
	printf("二叉树子系统\n");
	printf("==============================================\n");
	printf("||             1--建立新二叉树              ||\n");
	printf("||             2--广义表表示法显示          ||\n");
	printf("||             3--先序遍历                  ||\n");
	printf("||             4--中序遍历                  ||\n");
	printf("||             5--后序遍历                  ||\n");
	printf("||             6--层次遍历                  ||\n");
	printf("||             7--求叶子结点数              ||\n");
	printf("||             8--求二叉树总结点数          ||\n");
	printf("||             9--求二叉树的深度            ||\n");
	printf("||             0--返回                      ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-9):");
}

void btree() {
	BiTree T;
	int i, n;
	char ch1, ch2, a;
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue4();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("请输入二叉树结点('#'表示该结点为空):");
			CreateTree(&T);
			printf("二叉树建立成功");
			getchar();
			break;
		case '2':
			printf("二叉树的广义表表示法为:(");
			Print_Tree(T);
			printf(")");
			break;
		case '3':
			printf("二叉树的先序遍历序列为:");
			PreOrderTraverse(T);
			break;
		case '4':
			printf("二叉树的中序遍历序列为:");
			InOrderTraverse(T);
			break;
		case '5':
			printf("二叉树的后序遍历序列为:");
			PostOrderTraverse(T);
			break;
		case '6':
			printf("二叉树的层次遍历序列为:");
			LevelTraverse(T);
			break;
		case '7':
			printf("该二叉树有%d个叶子",TreeLeafNum(T));
			break;
		case '8':
			printf("该二叉树有%d个结点",TreeNodeNum(T));
			break;
		case '9':
			printf("该二叉树的深度为:%d",TreeDepth(T));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("输入错误,请输入0-9进行选择!");
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