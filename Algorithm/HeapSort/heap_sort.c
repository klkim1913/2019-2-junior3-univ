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

	printf("숫자들 입력: ");
	for (i = 1; i <= MAX_SIZE - 1; i++) {	// 숫자 입력
		scanf("%d", &heap[i]);
		size++;	// 힙 사이즈 증가		
		upHeap_max(heap, size);	// 들어갈때마다 힙 만들기
		//upHeap_min(heap, size);	// 들어갈때마다 힙 만들기(따로 실행)
		printHeap(heap, size);	// 힙 출력
	}
	printf("\n--------------------   MAX HEAP   ------------------------\n\n");
	//printf("\n--------------------   MIN HEAP   ------------------------\n\n");(따로 실행)
	heapSort_max(heap, size);	// 힙 정렬
	//heapSort_min(heap, size);	// 힙 정렬(따로 실행)

	return 0;
}

void swap(int heap[], int i1, int i2)	// 교환 함수
{
	int temp;

	temp = heap[i1];
	heap[i1] = heap[i2];
	heap[i2] = temp;
}

void printHeap(int heap[], int size)	// 힙 출력 함수
{
	int i;

	for (i = 1; i <= size; i++)
	{
		printf("%d ", heap[i]);
	}
	printf("\n");
}

void upHeap_max(int heap[], int size)	// max-heap 만들기
{
	int i, temp;

	i = size;	// 현재 삽입한 노드의 위치
	temp = heap[size];	// 현재 노드 값 저장
	while (i / 2 != 0)	// 루트면 종료
	{
		if (heap[i / 2] < temp)	// 부모보다 크면 올림
		{
			heap[i] = heap[i / 2];	// 현재 노드로 부모를 내리고
			i /= 2;					// 위치를 부모로 옮긴 뒤
		}
		else break;					// 부모보다 작으면 종료
	}
	heap[i] = temp;			// 최종 위치에 대입
}

void heapSort_max(int heap[], int size)
{
	int childi, parenti, temp;

	while (size > 0) {	// 다 정렬할때까지
		swap(heap, 1, size);	// 루트값을 뽑아서 마지막에 저장
		size--;
		parenti = 1;	// 부모 초기화
		childi = 2;	// 비교할 첫번째 자녀 위치 초기화
		temp = heap[1];	// 내려갈 값 저장
		while (childi <= size)	// 자녀가 있을경우에 다운 힙
		{
			if (childi < size)	// 오른쪽에도 자식이 있을경우에 자식값 결정하는 부분
			{
				if (heap[childi] < heap[childi + 1])	// 오른쪽 자식 값과 비교해서 크면
					childi++;	// 오른쪽 자식위치를 저장
			}
			if (temp < heap[childi])	// 자식이 더 크면
			{
				heap[parenti] = heap[childi];	// 자식 올리고
				parenti = childi;	// 자식위치가 다음에 비교할 부모위치 이므로
				childi = parenti * 2;	// 다음 부모의 자식위치 초기화
			}
			else break;		// 부모가 크면 종료
		}
		heap[parenti] = temp;	// 최종 위치에 저장
		printHeap(heap, MAX_SIZE - 1);	// 힙 출력
	}
}

void upHeap_min(int heap[], int size)	// min-heap 만들기
{
	int i, temp;

	i = size;	// 현재 삽입한 노드의 위치
	temp = heap[size];	// 현재 노드 값 저장
	while (i / 2 != 0)	// 루트면 종료
	{
		if (heap[i / 2] > temp)	// 부모보다 작으면 올림
		{
			heap[i] = heap[i / 2];	// 현재 노드로 부모를 내리고
			i /= 2;					// 위치를 부모로 옮긴 뒤
		}
		else break;					// 부모보다 크면 종료
		heap[i] = temp;			// 최종 위치에 대입
	}
}

void heapSort_min(int heap[], int size)
{
	int childi, parenti, temp;

	while (size > 0) {	// 다 정렬할때까지
		swap(heap, 1, size);	// 루트값을 뽑아서 마지막에 저장
		size--;
		parenti = 1;	// 부모 초기화
		childi = 2;	// 비교할 첫번째 자녀 위치 초기화
		temp = heap[1];	// 내려갈 값 저장
		while (childi <= size)	// 자녀가 있을경우에 다운 힙
		{
			if (childi < size)	// 오른쪽에도 자식이 있을경우에 자식값 결정하는 부분
			{
				if (heap[childi] > heap[childi + 1])	// 오른쪽 자식 값과 비교해서 작으면
					childi++;	// 오른쪽 자식위치를 저장
			}
			if (temp > heap[childi])	// 자식이 더 작으면
			{
				heap[parenti] = heap[childi];	// 자식 올리고
				parenti = childi;	// 자식위치가 다음에 비교할 부모위치 이므로
				childi = parenti * 2;	// 다음 부모의 자식위치 초기화
			}
			else break;		// 자식이 크면 종료
		}
		heap[parenti] = temp;	// 최종 위치에 저장
		printHeap(heap, MAX_SIZE - 1);	// 힙 출력
	}
}