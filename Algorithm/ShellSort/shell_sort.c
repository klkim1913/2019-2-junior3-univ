#include <stdio.h>

void ShellSort(int list[], int size);
void InsertionSort(int list[], int start, int end, int gap);
void PrintList(int list[], int size, int gap);

int main() {

	int arr1[11] = { 23,1,6,37,101,78,19,8,93,255,157 };
	int arr2[14] = { 54,12,76,435,21,96,81,221,154,762,326,72,11,55 };
	int size;

	size = sizeof(arr1) / sizeof(int);
	printf("�Է¹迭: ");
	PrintList(arr1, size, size + 1);
	ShellSort(arr1, size);	// �迭�� ��� ���� ����

	return 0;
}

void InsertionSort(int list[], int start, int end, int gap)	// start�� �κи���Ʈ �����ε���, end�� ��ü����Ʈ ������ �ε���, gap�� ����
{
	int i, j, key;

	for (i = start + gap; i <= end; i += gap) // �ι�° ��Һ��� ������ ��ұ��� ���ݸ�ŭ �̵�
	{
		key = list[i];	// ������ ��Ҹ� Ű�� ����
		for (j = i - gap; j >= start && list[j] > key; j-=gap) // �κи���Ʈ �ٷξպ��� ���س����鼭 ó������ ���ų� Ű������ ���� ���� ������ ����
		{
			list[j + gap] = list[j];	// ���������� ��ĭ�� �о�ֱ�
		}
		list[j + gap] = key;	// ���� j�� key���� �����Ƿ� �Ѱ��� �տ� Ű���� ����
	}
}
void ShellSort(int list[], int size) {

	int i, gap;

	for (gap = size / 2; gap >= 1; gap /= 2) // ������ ũ���� �ݾ� �ٿ�������.
	{
		if (gap % 2 == 0) gap++;	// ¦���ϰ�� �ߺ��� �������Ƿ� Ȧ���� ��´�.
		printf("���� %d ���� ��: ", gap);
		PrintList(list, size, gap);
		for (i = 0; i < gap; i++)	// �����ε����� �������� �κи���Ʈ�� �ϳ��� ����
		{
			InsertionSort(list, i, size - 1, gap);	// ��������
		}
		printf("���� %d ���� ��: ", gap);
		PrintList(list, size, gap);
	}
}

void PrintList(int list[], int size, int gap) {

	int i;

	for (i = 0; i < size; i++) {
		printf("%d ", list[i]);
		if ((i + 1) % gap == 0) printf("/ ");
	}
	printf("\n\n");
}