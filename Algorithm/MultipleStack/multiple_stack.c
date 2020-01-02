#include <stdio.h>

#define MAX_STACK_SIZE 8
#define STACK_NUM 2
#define TRUE 1
#define FALSE 0
#define ERROR -1

int stack[MAX_STACK_SIZE];
int top1, top2;

void initStack()	// 스택의 탑 초기화
{
	top1 = -1;
	top2 = MAX_STACK_SIZE;
}

int isFull()
{
	if (top2 == top1 + 1 || top1 == MAX_STACK_SIZE - 1 || top2 == 0) return TRUE;	// 탑포인터끼리 만나거나 스택1만 다차거나 스택2만 다찼거나
	else return FALSE;
}

int isEmpty()
{
	if (top1 == -1 && top2 == MAX_STACK_SIZE) return TRUE;	// 두개의 탑포인터 모두 안찼을 경우
	else return FALSE;
}

void push(int s, int e)		// 스택번호, 요소
{
	int i;

	if (isFull())	// 스택이 풀이면
	{
		if (s == 1)		// 1번스택에 요소가 들어왔다면
		{
			if (top1 == -1)	// 1번스택에 요소가 하나도 없다면 2번스택의 마지막을 지우게 함
			{
				for (i = MAX_STACK_SIZE - 1; i > 0; i--)	// top2요소까지 차례대로 뒤로 밈
				{
					stack[i] = stack[i - 1];
				}
				top2++;	// 2번스택이 하나 삭제되었으므로 역방향 증가
				top1++;	// 1번스택요소 1개 생성되었으므로
				stack[top1] = e;
			}
			else	// 그외의 경우
			{
				for (i = 0; i < top1; i++)	// top1요소까지 차례대로 앞으로 당김
				{
					stack[i] = stack[i + 1];
				}
				stack[top1] = e;	// 당긴후 탑포인터에 삽입
			}
		}
		else if (s == 2)	// 2번 스택에 요소가 들어왔다면
		{
			if (top2 == MAX_STACK_SIZE)	// 2번스택에 요소가 하나도 없다면 1번스택의 마지막을 지우게 함
			{
				for (i = 0; i < top1; i++)	// top1요소까지 차례대로 앞으로 당김
				{
					stack[i] = stack[i + 1];
				}
				top1--;	// 1번스택이 하나 삭제되었으므로 감소
				top2--;	// 2번스택요소 1개 생성되었으므로 역방향 감소
				stack[top2] = e;
			}
			else	// 그외의 경우
			{
				for (i = MAX_STACK_SIZE - 1; i > top2; i--)	// top2요소까지 차례대로 뒤로 밈
				{
					stack[i] = stack[i - 1];
				}
				stack[top2] = e;	// 당긴후 탑포인터에 삽입
			}
		}
	}
	else	// 스택이 풀이 아니면
	{
		if (s == 1)	// 1번스택 삽입
		{
			top1++;
			stack[top1] = e;
		}
		else if (s == 2)	// 2번스택 삽입
		{
			top2--;		// 반대방향이므로 감소
			stack[top2] = e;
		}
	}
}

int pop(int s)	// 스택번호
{
	int e;

	if (isEmpty())	// 비었을경우
	{
		printf("Stack Underflow!\n");
		return ERROR;
	}
	else
	{
		if (s == 1)	// 1번스택에서 꺼낼경우
		{
			e = stack[top1];
			top1--;
		}
		else if (s == 2)	// 2번스택에서 꺼낼경우
		{
			e = stack[top2];
			top2++;		// 반대방향이므로 증가
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
		printf("□");
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