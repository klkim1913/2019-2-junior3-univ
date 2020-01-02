#include <stdio.h>

#define MAX_SIZE 21

void swap(int heap[], int i1, int i2);
void printHeap(int heap[], int size);
void upHeap_max(int heap[], int size);
void heapSort_max(int heap[], int size);
void upHeap_min(int heap[], int size);
void heapSort_min(int heap[], int size);

int main() {

	int i, size = 0;
	int heap[MAX_SIZE];

	printf("���ڵ� �Է�: ");
	for (i = 1; i <= MAX_SIZE - 1; i++) {	// ���� �Է�
		scanf("%d", &heap[i]);
		size++;	// �� ������ ����		
		upHeap_max(heap, size);	// �������� �� �����
		//upHeap_min(heap, size);	// �������� �� �����(���� ����)
		printHeap(heap, size);	// �� ���
	}
	printf("\n--------------------   MAX HEAP   ------------------------\n\n");
	//printf("\n--------------------   MIN HEAP   ------------------------\n\n");(���� ����)
	heapSort_max(heap, size);	// �� ����
	//heapSort_min(heap, size);	// �� ����(���� ����)

	return 0;
}

void swap(int heap[], int i1, int i2)	// ��ȯ �Լ�
{
	int temp;

	temp = heap[i1];
	heap[i1] = heap[i2];
	heap[i2] = temp;
}

void printHeap(int heap[], int size)	// �� ��� �Լ�
{
	int i;

	for (i = 1; i <= size; i++)
	{
		printf("%d ", heap[i]);
	}
	printf("\n");
}

void upHeap_max(int heap[], int size)	// max-heap �����
{
	int i, temp;

	i = size;	// ���� ������ ����� ��ġ
	temp = heap[size];	// ���� ��� �� ����
	while (i / 2 != 0)	// ��Ʈ�� ����
	{
		if (heap[i / 2] < temp)	// �θ𺸴� ũ�� �ø�
		{
			heap[i] = heap[i / 2];	// ���� ���� �θ� ������
			i /= 2;					// ��ġ�� �θ�� �ű� ��
		}
		else break;					// �θ𺸴� ������ ����
	}
	heap[i] = temp;			// ���� ��ġ�� ����
}

void heapSort_max(int heap[], int size)
{
	int childi, parenti, temp;

	while (size > 0) {	// �� �����Ҷ�����
		swap(heap, 1, size);	// ��Ʈ���� �̾Ƽ� �������� ����
		size--;
		parenti = 1;	// �θ� �ʱ�ȭ
		childi = 2;	// ���� ù��° �ڳ� ��ġ �ʱ�ȭ
		temp = heap[1];	// ������ �� ����
		while (childi <= size)	// �ڳడ ������쿡 �ٿ� ��
		{
			if (childi < size)	// �����ʿ��� �ڽ��� ������쿡 �ڽİ� �����ϴ� �κ�
			{
				if (heap[childi] < heap[childi + 1])	// ������ �ڽ� ���� ���ؼ� ũ��
					childi++;	// ������ �ڽ���ġ�� ����
			}
			if (temp < heap[childi])	// �ڽ��� �� ũ��
			{
				heap[parenti] = heap[childi];	// �ڽ� �ø���
				parenti = childi;	// �ڽ���ġ�� ������ ���� �θ���ġ �̹Ƿ�
				childi = parenti * 2;	// ���� �θ��� �ڽ���ġ �ʱ�ȭ
			}
			else break;		// �θ� ũ�� ����
		}
		heap[parenti] = temp;	// ���� ��ġ�� ����
		printHeap(heap, MAX_SIZE - 1);	// �� ���
	}
}

void upHeap_min(int heap[], int size)	// min-heap �����
{
	int i, temp;

	i = size;	// ���� ������ ����� ��ġ
	temp = heap[size];	// ���� ��� �� ����
	while (i / 2 != 0)	// ��Ʈ�� ����
	{
		if (heap[i / 2] > temp)	// �θ𺸴� ������ �ø�
		{
			heap[i] = heap[i / 2];	// ���� ���� �θ� ������
			i /= 2;					// ��ġ�� �θ�� �ű� ��
		}
		else break;					// �θ𺸴� ũ�� ����
		heap[i] = temp;			// ���� ��ġ�� ����
	}
}

void heapSort_min(int heap[], int size)
{
	int childi, parenti, temp;

	while (size > 0) {	// �� �����Ҷ�����
		swap(heap, 1, size);	// ��Ʈ���� �̾Ƽ� �������� ����
		size--;
		parenti = 1;	// �θ� �ʱ�ȭ
		childi = 2;	// ���� ù��° �ڳ� ��ġ �ʱ�ȭ
		temp = heap[1];	// ������ �� ����
		while (childi <= size)	// �ڳడ ������쿡 �ٿ� ��
		{
			if (childi < size)	// �����ʿ��� �ڽ��� ������쿡 �ڽİ� �����ϴ� �κ�
			{
				if (heap[childi] > heap[childi + 1])	// ������ �ڽ� ���� ���ؼ� ������
					childi++;	// ������ �ڽ���ġ�� ����
			}
			if (temp > heap[childi])	// �ڽ��� �� ������
			{
				heap[parenti] = heap[childi];	// �ڽ� �ø���
				parenti = childi;	// �ڽ���ġ�� ������ ���� �θ���ġ �̹Ƿ�
				childi = parenti * 2;	// ���� �θ��� �ڽ���ġ �ʱ�ȭ
			}
			else break;		// �ڽ��� ũ�� ����
		}
		heap[parenti] = temp;	// ���� ��ġ�� ����
		printHeap(heap, MAX_SIZE - 1);	// �� ���
	}
}