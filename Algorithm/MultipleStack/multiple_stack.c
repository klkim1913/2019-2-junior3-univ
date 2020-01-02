#include <stdio.h>

#define MAX_STACK_SIZE 8
#define STACK_NUM 2
#define TRUE 1
#define FALSE 0
#define ERROR -1

int stack[MAX_STACK_SIZE];
int top1, top2;

void initStack()	// ������ ž �ʱ�ȭ
{
	top1 = -1;
	top2 = MAX_STACK_SIZE;
}

int isFull()
{
	if (top2 == top1 + 1 || top1 == MAX_STACK_SIZE - 1 || top2 == 0) return TRUE;	// ž�����ͳ��� �����ų� ����1�� �����ų� ����2�� ��á�ų�
	else return FALSE;
}

int isEmpty()
{
	if (top1 == -1 && top2 == MAX_STACK_SIZE) return TRUE;	// �ΰ��� ž������ ��� ��á�� ���
	else return FALSE;
}

void push(int s, int e)		// ���ù�ȣ, ���
{
	int i;

	if (isFull())	// ������ Ǯ�̸�
	{
		if (s == 1)		// 1�����ÿ� ��Ұ� ���Դٸ�
		{
			if (top1 == -1)	// 1�����ÿ� ��Ұ� �ϳ��� ���ٸ� 2�������� �������� ����� ��
			{
				for (i = MAX_STACK_SIZE - 1; i > 0; i--)	// top2��ұ��� ���ʴ�� �ڷ� ��
				{
					stack[i] = stack[i - 1];
				}
				top2++;	// 2�������� �ϳ� �����Ǿ����Ƿ� ������ ����
				top1++;	// 1�����ÿ�� 1�� �����Ǿ����Ƿ�
				stack[top1] = e;
			}
			else	// �׿��� ���
			{
				for (i = 0; i < top1; i++)	// top1��ұ��� ���ʴ�� ������ ���
				{
					stack[i] = stack[i + 1];
				}
				stack[top1] = e;	// ����� ž�����Ϳ� ����
			}
		}
		else if (s == 2)	// 2�� ���ÿ� ��Ұ� ���Դٸ�
		{
			if (top2 == MAX_STACK_SIZE)	// 2�����ÿ� ��Ұ� �ϳ��� ���ٸ� 1�������� �������� ����� ��
			{
				for (i = 0; i < top1; i++)	// top1��ұ��� ���ʴ�� ������ ���
				{
					stack[i] = stack[i + 1];
				}
				top1--;	// 1�������� �ϳ� �����Ǿ����Ƿ� ����
				top2--;	// 2�����ÿ�� 1�� �����Ǿ����Ƿ� ������ ����
				stack[top2] = e;
			}
			else	// �׿��� ���
			{
				for (i = MAX_STACK_SIZE - 1; i > top2; i--)	// top2��ұ��� ���ʴ�� �ڷ� ��
				{
					stack[i] = stack[i - 1];
				}
				stack[top2] = e;	// ����� ž�����Ϳ� ����
			}
		}
	}
	else	// ������ Ǯ�� �ƴϸ�
	{
		if (s == 1)	// 1������ ����
		{
			top1++;
			stack[top1] = e;
		}
		else if (s == 2)	// 2������ ����
		{
			top2--;		// �ݴ�����̹Ƿ� ����
			stack[top2] = e;
		}
	}
}

int pop(int s)	// ���ù�ȣ
{
	int e;

	if (isEmpty())	// ��������
	{
		printf("Stack Underflow!\n");
		return ERROR;
	}
	else
	{
		if (s == 1)	// 1�����ÿ��� �������
		{
			e = stack[top1];
			top1--;
		}
		else if (s == 2)	// 2�����ÿ��� �������
		{
			e = stack[top2];
			top2++;		// �ݴ�����̹Ƿ� ����
		}
		return e;
	}
}

void printStack()
{
	int i;

	for (i = 0; i <= top1; i++)
		printf(" %d", stack[i]);
	printf(" /");
	for (i = 0; i < top2 - top1 - 1; i++)
		printf("��");
	printf(" /");
	for (i = top2; i < MAX_STACK_SIZE; i++)
		printf(" %d", stack[i]);
	printf("\n");
}
int main()
{
	initStack();

	push(1, 2);
	printStack();
	push(2, 4);
	printStack();
	push(1, 1);
	printStack();
	push(1, 5);
	printStack();
	push(2, 6);
	printStack();
	push(1, 3);
	printStack();
	push(2, 7);
	printStack();
	push(2, 8);
	printStack();
	pop(1);
	printStack();
	push(1, 10);
	printStack();
	push(1, 11);
	printStack();
	push(2, 22);
	printStack();
	pop(2);
	printStack();
	push(2, 31);
	printStack();
	push(2, 55);
	printStack();
	
	return 0;
}