#pragma once
/*
基于链表的停车场管理系统
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <time.h>
#define ERROR 0
#define OK 1
typedef int Status;
typedef struct {//车
	int start;//进入时间
	int end;//离开时间
	int cost;//商场花费金额
	char id[10];//车牌号
}CarOwner;

typedef struct TCNode {//停车场车位
	CarOwner data;//数据
	struct TCNode *next;
}TCNode, *TCLinkList;

Status ParkingLot_Init(TCLinkList *L) {
	*L = (TCLinkList)malloc(sizeof(TCNode));
	if (!(*L))
		return ERROR;
	(*L)->next = NULL;
	return OK;
}


int ParkingLot_Num(TCLinkList L) {//停车场已用车位(0-100)
	TCLinkList p = L;
	int len = 0;
	while (p->next) {
		len++;
		p = p->next;
	}
	return len;
}


Status ParkingLot_Insert(TCLinkList *L, CarOwner e) {
	TCLinkList p, s;
	p = *L;
	while (p->next) 
		p = p->next;
	
	s = (TCLinkList)malloc(sizeof(TCNode));
	s->data = e;
	s->next = p->next;
	p->next = s;
	return OK;
}


Status ParkingLot_Delete(TCLinkList*L, char i[]) {//通过车牌号来删除
	int j = 0;
	TCLinkList p, q;
	p = *L;
	while (p) {
		if (strcmp(i, p->next->data.id) == 0) {
			break;
		}
		p = p->next;
		j++;
	}
	if (j > ParkingLot_Num(*L)) 
		return ERROR;

	q = p->next;
	p->next = q->next;
	free(q);
	return OK;
}


//进入
Status Enter(TCLinkList *L, CarOwner h) {
	int num = ParkingLot_Num(*L);
	if (num >= 100) {
		printf("车位已满!");
		return ERROR;
	}
	ParkingLot_Insert(L, h);
	printf("您已进入停车场");
	return OK;
}


void Update(CarOwner *h) {//采用随机数模拟消费和停车时长
	//涉及停车费用计算和消费满减
	h->cost = rand() % 2000 + 1;
	h->end = rand() % 11 + 1;
}


//离开
void Leave(TCLinkList *L, CarOwner h) {
	if (h.cost >= 200)
		printf("商场消费超过200RMB，停车费减半，共需支付%dRMB\n", (h.end - h.start)*3);
	else
		printf("共需支付停车费%dRMB\n", (h.end - h.start) * 6);
	ParkingLot_Delete(L, h.id);
	printf("车牌号:%s的车主,",h.id);
	printf("您已离开停车场");
}

void TCLPrint(TCLinkList L) {
	TCLinkList p;
	p = L->next;
	while (p) {
		printf("%s\n",p->data.id);
		p = p->next;
	}
}

void Menue8() {
	printf("停车场管理子系统\n");
	printf("==============================================\n");
	printf("||           1--进入停车场                  ||\n");
	printf("||           2--更新车主消费信息并离开停车场||\n");
	printf("||           3--显示停车场车辆              ||\n");
	printf("||           4--获取停车场车辆数量          ||\n");
	printf("||           0--返回                        ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-3):");
}

void parkinglot() {
	TCLinkList L;
	ParkingLot_Init(&L);
	CarOwner h;
	int i, n;
	char ch1, ch2, a,s[10];
	ch1 = 'y';
	while (ch1 == 'y' || ch1 == 'Y') {
		Menue8();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			printf("请输入您的车牌号:");
			scanf("%s", &h.id);
			Enter(&L, h);
			h.start = 0;
			getchar();
			break;
		case '2':
			printf("请输入您的车牌号:");
			scanf("%s",&s);
			strcpy(h.id, s);
			Update(&h);
			Leave(&L,h);
			getchar();
			break;
		case '3':
			printf("停车场车辆有:\n");
			TCLPrint(L);
			break;
		case '4':
			printf("当前停车场有%d辆汽车",ParkingLot_Num(L));
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("输入错误,请输入0-3进行选择!");
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