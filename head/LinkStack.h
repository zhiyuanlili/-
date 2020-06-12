//#pragma once
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define ERROR 0
#define OK 1
typedef char ElemType_S;
typedef int Status;

//定义两种不同类型的栈便于中缀表达式转后缀表达式计算
//字符栈
typedef struct StackNode {
	ElemType_S data;
	struct StackNode*next;
}StackNode, *LinkStackPtr;

typedef struct LinkStack {
	LinkStackPtr top;
	int count;
}LinkStack;

//数字栈
typedef struct StackNode_num {
	int data;
	struct StackNode_num*next;
}StackNode_num, *LinkStackPtr_num;

typedef struct LinkStack_num {
	LinkStackPtr_num top;
	int count;
}LinkStack_num;


//初始化
Status InitStack(LinkStack *s) {
	s->top = (LinkStackPtr)malloc(sizeof(StackNode));
	s->top = NULL;
	s->count = 0;
	return OK;
}
Status InitStack_num(LinkStack_num *s) {//数字栈
	s->top = (LinkStackPtr_num)malloc(sizeof(StackNode_num));
	s->top = NULL;
	s->count = 0;
	return OK;
}

//入栈
Status Push(LinkStack*S, ElemType_S e) {
	LinkStackPtr p = (LinkStackPtr)malloc(sizeof(StackNode));
	p->data = e;
	p->next = S->top;
	S->top = p;
	S->count++;
	return OK;
}
Status Push_num(LinkStack_num*S, int e) {
	LinkStackPtr_num p = (LinkStackPtr_num)malloc(sizeof(StackNode_num));
	p->data = e;
	p->next = S->top;
	S->top = p;
	S->count++;
	return OK;
}

//出栈
Status Pop(LinkStack*S, ElemType_S*e) {
	LinkStackPtr p;
	if (!S->top)
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	S->count--;
	free(p);
	return OK;
}
Status Pop_num(LinkStack_num*S, int*e) {
	LinkStackPtr_num p;
	if (!S->top)
		return ERROR;
	*e = S->top->data;
	p = S->top;
	S->top = S->top->next;
	S->count--;
	free(p);
	return OK;
}

//进制转换
LinkStack_num BinaryConversion(int num) {
	LinkStack_num S;
	InitStack_num(&S);
	while (num) {
		Push_num(&S, num % 2);
		num /= 2;
	}
	return S;
}

Status EmptyStack(LinkStack_num *S) {
	if (S->top == NULL) {
		return ERROR;
	}
	return OK;
}

Status GetTop(LinkStack_num *S) {
	if (EmptyStack(S) == 0)
		return ERROR;

	return S->top->data;
}

//打印
void PrintStack(LinkStack*S) {
	LinkStackPtr p = S->top;
	if (!p)
		return;
	while (p) {
		printf("%-c", p->data);
		p = p->next;
	}
	printf("\n");
}

void PrintStack_num(LinkStack_num*S) {
	LinkStackPtr_num p = S->top;
	if (!p)
		return;
	while (p) {
		printf("%-5d", p->data);
		p = p->next;
	}
	printf("\n");
}


//判断优先级,用于表达式计算功能
int level(char a) {
	if (a == '+' || a == '-')
		return 1;
	else if (a == '*' || a == '/')
		return 2;
	else if (a == '(')
		return 1;
	else if (a == ')')
		return -1;
}


/*
中缀表达式转后缀表达式
9 +（3 - 1）* 3 + 10 / 2    ---->   9 3 1 - 3 *+ 10 2 /+
*/
int Mid_to_Rear(ElemType_S *data, LinkStack *S) {
	int len = strlen(data);
	int i, k = 0, flag = 1;
	ElemType_S e;
	for (i = 0;i < len;i++) {
		if (data[i] <= '9'&&data[i] >= '0') {
			data[k] = data[i];
			k++;
			/*if (data[i + 1] <= '9'&&data[i] >= '0'&&data[i])
			continue;
			else {
			data[]
			}*/
		}
		else if (flag) {
			//第一个非数字字符进栈
			Push(S, data[i]);
			flag = 0;
		}
		else if (data[i] == ' ') {
			data[k] = data[i];
			k++;
		}
		else if (level(data[i]) >= level(S->top->data)) {
			//优先级和栈定元素的优先级比较，如果优先级大于或者等于则入栈
			Push(S, data[i]);
		}
		else if (level(data[i]) < level(S->top->data)) {
			//大于则出栈，一直出到没有比这个优先级更小
			if (level(data[i]) == -1) {
				//当出现')'时，一直出栈到'('。
				//printf("匹配到了括号\n");
				while (S->top->data != '('&&S->top) {
					Pop(S, &e);
					data[k] = e;
					k++;
				}
				Pop(S, &e);
			}
			else {
				while ((level(data[i]) <= level(S->top->data)) && S->top) {
					Pop(S, &e);
					data[k] = e;
					k++;
					if (!S->top)
						break;
				}
				Push(S, data[i]);
			}
		}
	}
	while (S->top) {//将栈里剩下的符号移出
		Pop(S, &e);
		data[k] = e;
		k++;
	}
	return k;
}


//后缀表达式计算
Status Cal(LinkStack_num *S, ElemType_S *data, int k) {//S为数字栈，data数组为后缀表达式，k为data数组的位数
	int result = 0, i, j = -1, x = 0, num1, num2;//9   3  1 -  3 *+ 10  2/+
	for (i = 0;i < k;i++) {
		j = -1;
		if (data[i] == ' ') {
			continue;
		}
		else if (data[i] >= '0'&&data[i] <= '9') {
			if (data[i + 1] >= '0'&&data[i + 1] <= '9') {
				j = i + 1;
				x = x * 10 + data[i] - '0';
				while (data[j] >= '0'&&data[j] <= '9'&&j<k) {
					x = x * 10 + data[j] - '0';
					j++;
					i++;
				}
				i++;
			}
			if (j == -1)
				x = x * 10 + data[i] - '0';
			Push_num(S, x);
			x = 0;

		}
		else {
			Pop_num(S, &num2);
			Pop_num(S, &num1);
			switch (data[i]) {
			case '+':
				result = num1 + num2;
				break;
			case '-':
				result = num1 - num2;
				break;
			case '*':
				result = num1 * num2;
				break;
			case '/':
				result = num1 / num2;
				break;
			}
			Push_num(S, result);
		}
	}
	return result;
}

void han(int n, char a, char b, char c) {
	if (n == 1)
		printf("从 %c 到 %c\n", a, c);
	else {
		han(n - 1, a, c, b);
		printf("从 %c 到 %c\n", a, c);
		han(n - 1, b, a, c);
	}
}

void Menue1() {
	//菜单
	printf("栈子系统\n");
	printf("==============================================\n");
	printf("||               1--初始化栈                ||\n");
	printf("||               2--入栈                    ||\n");
	printf("||               3--出栈                    ||\n");
	printf("||               4--求栈顶元素              ||\n");
	printf("||               5--显示栈中元素            ||\n");
	printf("||               6--十、二进制转换          ||\n");
	printf("||               7--表达式转换并求值        ||\n");
	printf("||               8--汉诺塔移动步骤          ||\n");
	printf("||               0--返回                    ||\n");
	printf("==============================================\n");
	printf("请输入菜单号(0-6):");
}

void linkstack() {
	int i, e, n, result;
	LinkStack_num S;
	char ch1, ch2, data[200], a;
	ch1 = 'y';
	LinkStack N;
	InitStack(&N);

	while (ch1 == 'y' || ch1 == 'Y') {
		Menue1();
		scanf("%c", &ch2);
		getchar();
		switch (ch2) {
		case '1':
			InitStack_num(&S);
			printf("初始化完成");
			break;
		case '2':
			printf("请输入要入栈的元素个数:");
			scanf("%d", &n);
			printf("请输入入栈元素:");
			for (i = 0;i < n;i++) {
				scanf("%d", &e);
				Push_num(&S, e);
			}
			printf("入栈后为:");
			PrintStack_num(&S);
			getchar();
			break;
		case '3':
			printf("请输入要出栈的元素个数:");
			scanf("%d", &n);
			printf("出栈元素为:");
			for (i = 0;i < n;i++) {
				Pop_num(&S, &e);
				printf("%-5d", e);
			}
			getchar();
			break;
		case '4':
			e = GetTop(&S);
			printf("栈顶元素为:%d", e);
			break;
		case '5':
			printf("栈中元素为:");
			PrintStack_num(&S);
			break;
		case '6':
			printf("请输入十进制正整数:");
			scanf("%d", &e);
			printf("转换成二进制为:");
			PrintStack_num(&(BinaryConversion(e)));
			getchar();
			break;
		case '7':
			printf("请输入一个算术表达式(只有+、-、*、/四种运算,每个元素中间用空格隔开):");
			gets_s(data);
			n = Mid_to_Rear(data, &N);
			printf("中缀表达式转后缀表达式后为:");
			for (i = 0;i < n;i++)
				printf("%c", data[i]);
			result = Cal(&S, data, n);
			printf("\n表达式的值为:%d", result);
			break;
		case '8':
			printf("请输入A塔有多少层n:");
			scanf("%d",&n);
			printf("有三个底座A、B、C,A底座上有%d层,将A移动到C上需要经过:\n",n);
			han(n, 'A', 'B', 'C');
			getchar();
			break;
		case '0':
			ch1 = 'n';
			break;
		default:
			printf("输入错误,请重新输入选择!");
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
